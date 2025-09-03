#include <Wire.h>
#include <BH1750.h>
#include <OLED_I2C.h>

OLED oled(SDA, SCL, 8);
BH1750 lightMeter; //BH1750의 이름을 lightMeter으로 설정
extern uint8_t SmallFont[]; //글꼴 배열 외부에서 가져옴

#define pt_1 A1
#define pt_2 A2

void setup() {
  Wire.begin();
  lightMeter.begin();
  oled.begin();
  oled.setFont(SmallFont); //글꼴 설정
}
void loop() {
  oled.clrScr(); //디스플레이 지움

  int ai_1 = analogRead(pt_1);
  ai_1 = map(ai_1, 0, 1023, 400, 1000);
  int ai_2 = analogRead(pt_2);
  ai_2 = map(ai_2, 0, 1023, 10, 120);
  char ai_1_str[6];
  char ai_2_str[6];
  itoa(ai_1, ai_1_str, 10);
  itoa(ai_2, ai_2_str, 10); //int형을 문자열로 변환하여 str 배열에 저장(oled에 int 출력 불가)

  int ai_1_len = strlen(ai_1_str);
  int ai_1_x = 66 - ai_1_len * 6; // 오른쪽 끝에 정렬된 X 좌표 계산(글꼴 너비 6)

  int ai_2_len = strlen(ai_2_str);
  int ai_2_x = 66 - ai_2_len * 6; // 오른쪽 끝에 정렬된 X 좌표 계산(글꼴 너비 6)

  oled.print("set: ", 0, 0);
  oled.print(ai_1_str, ai_1_x, 0); // 오른쪽 정렬
  oled.print("lx", 70, 0);

  float lux = lightMeter.readLightLevel(); //lux라는 변수를 만들고 측정값을 저장
  char buf[10]; // 문자열을 저장할 버퍼
  dtostrf(lux, 6, 0, buf); // float 값을 문자열로 변환하여 버퍼에 저장 - 소수점 자리수 0(oled에 float 출력 불가)
  oled.print("now: ", 0, 11);
  oled.print(buf, 30, 11);
  oled.print("lx", 70, 11);
  oled.print("dur: ", 0, 33);
  oled.print(ai_2_str, ai_2_x, 33); // 오른쪽 정렬
  oled.print("s", 70, 33);
  oled.print("pir: ", 0, 44);
  oled.update(); //디스플레이 업데이트(반영)
  delay(100);
}