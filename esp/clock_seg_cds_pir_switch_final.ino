/*
 * ESP32-C3 WiFi 시계 (---- + 콜론 깜빡 = 동기화 표시 버전)
 * - 시각을 받기 전에는 ---- 를 띄우고 콜론을 깜빡임(= 동기화 시도 중)
 * - 동기화 시도: 부팅 / 매일 05:00 / 17:00 / 실패 시 8초마다 재시도
 * - WiFi: C3 미니 약점 보정(절전 끔 + TX파워 낮춤) + 빠른 재시도
 * - PIR 모드에서 사람 없으면 화면 꺼짐, 모드 스위치(푸시락) PIR<->상시
 * - CdS 자동 밝기(최고 2단계로 제한)
 * 주의: 배터리 RTC 없어 전원이 오래 끊기면 시각이 사라져 ----가 뜸
 */
#include <WiFi.h>
#include <time.h>
#include <sys/time.h>
#include "esp_sntp.h"
#include <TM1637Display.h>

// ===================== 사용자 설정 =====================
const char* WIFI_SSID = "id";
const char* WIFI_PASS = "pasword";

#define CLK      4
#define DIO      5
#define CDS      3
#define PIR      10
#define MODE_SW  6

const char* TZ_INFO = "KST-9";
const char* NTP1 = "kr.pool.ntp.org";
const char* NTP2 = "pool.ntp.org";
const char* NTP3 = "time.google.com";

#define HOLD_MS        20000UL
#define REFRESH_MS     1000UL
#define BLINK_MS       500UL
#define WIFI_TIMEOUT   25000UL   // 한 번 시도에서 연결 대기(DHCP 포함 여유)
#define NTP_TIMEOUT    15000UL   // 연결 후 NTP 응답 대기
#define SYNC_RETRY_MS  8000UL    // 실패 시 재시도 간격(짧게 → 빨리 다시 시도)
#define SW_DEBOUNCE    800UL     // 스위치 디바운스(흔들리는 신호 무시)

// C3 미니 안테나 약점 보정용 TX 파워. 안 붙으면 11/7dBm 등으로 바꿔보세요.
#define WIFI_TX_POWER  WIFI_POWER_8_5dBm
// ======================================================

TM1637Display display(CLK, DIO);

const uint8_t COLON = 0b01000000;
const uint8_t DP    = 0x80;

const uint8_t L_P = SEG_A | SEG_B | SEG_E | SEG_F | SEG_G;
const uint8_t L_I = SEG_E | SEG_F;
const uint8_t L_r = SEG_E | SEG_G;
const uint8_t MSG_PIR[]  = { L_P, L_I, L_r, 0x00 };
const uint8_t MSG_8888[] = { 0x7F, 0x7F, 0x7F, 0x7F };

unsigned long lastMotion  = 0;
unsigned long lastRefresh = 0;
bool displayOn = false;
bool alwaysOn  = false;

int swStable = HIGH, swLast = HIGH;
unsigned long swT = 0;

enum { SY_IDLE, SY_CONNECTING, SY_WAIT_NTP } syncStage = SY_IDLE;
unsigned long syncStageT0 = 0;
unsigned long lastSyncTry = 0;
bool syncPending = false;
int  prevHour = -1;
volatile bool ntpGotTime = false;

void onNtpSync(struct timeval *tv) { ntpGotTime = true; }

int cdsToBrightness(int light) {
  if (light >= 3000) return 2;
  if (light >= 1500) return 1;
  return 0;
}

int readLight() {
  long sum = 0;
  for (int i = 0; i < 10; i++) sum += analogRead(CDS);
  return sum / 10;
}

void refreshDisplay() {
  display.setBrightness(cdsToBrightness(readLight()));
  bool colon = syncPending && (((millis() / BLINK_MS) % 2) == 0);
  struct tm t;
  if (getLocalTime(&t, 0)) {
    display.showNumberDecEx(t.tm_hour * 100 + t.tm_min, colon ? COLON : 0, true);
  } else {
    uint8_t seg[4] = { SEG_G, SEG_G, SEG_G, SEG_G };
    if (colon) seg[1] |= DP;
    display.setSegments(seg);
  }
}

// --- WiFi 헬퍼: C3 미니 보정 설정을 매 시도마다 일괄 적용 ---
void startSyncAttempt() {
  ntpGotTime = false;
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);              // 모뎀 절전 끔 → 연결 안정성↑
  WiFi.setTxPower(WIFI_TX_POWER);    // C3 미니 안테나 약점 보정(핵심)
  WiFi.begin(WIFI_SSID, WIFI_PASS);
}

void stopWifi() {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

// 논블로킹 동기화 처리 (화면을 멈추지 않음)
void serviceSync() {
  switch (syncStage) {
    case SY_IDLE:
      if (syncPending && millis() - lastSyncTry >= SYNC_RETRY_MS) {
        lastSyncTry = millis();
        startSyncAttempt();
        syncStage   = SY_CONNECTING;
        syncStageT0 = millis();
      }
      break;

    case SY_CONNECTING:
      if (WiFi.status() == WL_CONNECTED) {
        configTzTime(TZ_INFO, NTP1, NTP2, NTP3);
        syncStage   = SY_WAIT_NTP;
        syncStageT0 = millis();
      } else if (millis() - syncStageT0 >= WIFI_TIMEOUT) {
        stopWifi();
        syncStage = SY_IDLE;          // SYNC_RETRY_MS 뒤 곧바로 재시도
      }
      break;

    case SY_WAIT_NTP:
      if (ntpGotTime) {
        syncPending = false;          // 성공 → 콜론 멈춤
        stopWifi();
        syncStage = SY_IDLE;
      } else if (millis() - syncStageT0 >= NTP_TIMEOUT) {
        stopWifi();
        syncStage = SY_IDLE;          // 재시도(콜론 계속 깜빡)
      }
      break;
  }
}

void showModeMessage() {
  display.setBrightness(cdsToBrightness(readLight()));
  display.setSegments(alwaysOn ? MSG_8888 : MSG_PIR);
  delay(2000);
  displayOn   = true;
  lastMotion  = millis();
  lastRefresh = millis() - REFRESH_MS;
}

void setup() {
  pinMode(PIR, INPUT);
  pinMode(MODE_SW, INPUT_PULLUP);
  WiFi.persistent(false);            // flash 기록 안 함(빠르고 수명↑)
  setenv("TZ", TZ_INFO, 1);
  tzset();

  sntp_set_time_sync_notification_cb(onNtpSync);

  swStable = swLast = digitalRead(MODE_SW);
  alwaysOn = (swStable == HIGH);

  display.setBrightness(2);

  syncPending = true;
  lastSyncTry = millis() - SYNC_RETRY_MS;   // 부팅 즉시 첫 시도
  lastMotion  = millis();
}

void loop() {
  unsigned long now = millis();

  // 1) 모드 스위치(푸시락) 전환 감지
  int sw = digitalRead(MODE_SW);
  if (sw != swLast) { swLast = sw; swT = now; }
  if (now - swT > SW_DEBOUNCE && sw != swStable) {
    swStable = sw;
    alwaysOn = (swStable == HIGH);
    showModeMessage();
    now = millis();
  }

  // 2) 매일 05:00 / 17:00 진입 순간에 동기화 예약
  struct tm tnow;
  if (getLocalTime(&tnow, 0)) {
    if (tnow.tm_hour != prevHour) {
      if (tnow.tm_hour == 5 || tnow.tm_hour == 17) syncPending = true;
      prevHour = tnow.tm_hour;
    }
  }

  // 3) 동기화 처리(논블로킹)
  serviceSync();

  // 4) PIR
  if (digitalRead(PIR) == HIGH) lastMotion = now;
  bool wantOn = alwaysOn || ((now - lastMotion) < HOLD_MS);

  // 5) 화면 끄기
  if (!wantOn) {
    if (displayOn) {
      display.setBrightness(0, false);
      display.clear();
      displayOn = false;
    }
    delay(20);
    return;
  }

  // 6) 막 켜질 때 즉시 갱신
  if (!displayOn) {
    displayOn = true;
    lastRefresh = now - REFRESH_MS;
  }

  // 7) 표시
  unsigned long interval = syncPending ? BLINK_MS : REFRESH_MS;
  if (now - lastRefresh >= interval) {
    lastRefresh = now;
    refreshDisplay();
  }

  delay(20);
}