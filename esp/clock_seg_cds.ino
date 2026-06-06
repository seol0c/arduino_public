/*
 * ESP32-C3 WiFi 시계 (CdS 자동 밝기 버전)
 * - 첫 동기화 후엔 인터넷이 끊겨도 내부 시계로 계속 시간 표시
 * - 12시간마다 '조용히' 뒤에서 재동기화 (화면에 ---- 안 뜨고 시계 안 멈춤)
 * - 콜론 고정, CdS 자동 밝기
 * - PIR 제거 → 화면은 항상 켜져 있음
 */
#include <WiFi.h>
#include <time.h>
#include <TM1637Display.h>
// ===================== 사용자 설정 =====================
const char* WIFI_SSID = "0cg";
const char* WIFI_PASS = "123789456";
#define CLK  4
#define DIO  5
#define CDS  3
const long  GMT_OFFSET_SEC = 9 * 3600;   // 한국 UTC+9
const int   DST_OFFSET_SEC = 0;
#define SYNC_INTERVAL  43200000UL        // 재동기화 주기 (12시간)
#define REFRESH_MS     1000UL            // 화면 갱신 주기
#define WIFI_TIMEOUT   20000UL           // 한 번 연결 시도 제한시간
// ======================================================
TM1637Display display(CLK, DIO);
const uint8_t DASHES[] = { SEG_G, SEG_G, SEG_G, SEG_G };
const uint8_t COLON = 0b01000000;
unsigned long lastSync    = 0;
unsigned long lastRefresh = 0;
bool timeIsSet  = false;   // 시각을 한 번이라도 맞췄는가
int cdsToBrightness(int light) {
  if (light >= 3000) return 4;
  if (light >= 2000) return 3;
  if (light >= 1000) return 2;
  if (light >= 500)  return 1;
  return 0;
}
int readLight() {
  long sum = 0;
  for (int i = 0; i < 10; i++) sum += analogRead(CDS);
  return sum / 10;
}
// WiFi 켜서 시각 동기화 후 끔. 화면은 건드리지 않음(조용히)
bool syncTime() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < WIFI_TIMEOUT) {
    delay(250);
  }
  bool ok = false;
  if (WiFi.status() == WL_CONNECTED) {
    configTime(GMT_OFFSET_SEC, DST_OFFSET_SEC,
               "kr.pool.ntp.org", "pool.ntp.org", "time.google.com");
    struct tm t;
    if (getLocalTime(&t, 10000)) ok = true;
  }
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  return ok;
}
void setup() {
  display.setBrightness(2);
  display.setSegments(DASHES);   // 첫 동기화 동안만 ----
  // 첫 시각을 맞출 때까지만 기다림 (그동안 ----)
  while (!syncTime()) {
    delay(2000);
  }
  timeIsSet = true;
  lastSync  = millis();
}
void loop() {
  unsigned long now = millis();
  // 12시간마다 조용히 재동기화 (성공이든 실패든 화면은 시계 그대로)
  if (now - lastSync >= SYNC_INTERVAL) {
    syncTime();           // 실패해도 내부 시계는 계속 흐름
    lastSync = millis();  // 다음 주기까지 대기 (실패해도 12시간 뒤 재시도)
  }
  // 시각 표시 (콜론 고정, CdS 자동 밝기). 화면은 항상 켜둠
  if (now - lastRefresh >= REFRESH_MS) {
    lastRefresh = now;
    struct tm t;
    if (getLocalTime(&t)) {
      int hhmm = t.tm_hour * 100 + t.tm_min;
      display.setBrightness(cdsToBrightness(readLight()));
      display.showNumberDecEx(hhmm, COLON, true);
    }
  }
  delay(20);
}
