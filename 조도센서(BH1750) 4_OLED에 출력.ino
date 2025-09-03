#include <Wire.h>
#include <BH1750.h>
#include <OLED_I2C.h>

OLED oled(SDA, SCL, 8);
BH1750 lightMeter; //BH1750의 이름을 lightMeter으로 설정
extern uint8_t SmallFont[]; //글꼴 배열 외부에서 가져옴

void setup() {
  Wire.begin();
  lightMeter.begin();
  oled.begin();
  oled.setFont(SmallFont); //글꼴 설정
}
void loop() {
  float lux = lightMeter.readLightLevel(); //lux라는 변수를 만들고 측정값을 저장
  char buf[10]; // 문자열을 저장할 버퍼
  dtostrf(lux, 6, 2, buf); // float 값을 문자열로 변환하여 버퍼에 저장(oled에 float 출력 불가)
  oled.clrScr(); //디스플레이 지움
  oled.print("set: ", 0, 0);
  oled.print("now: ", 0, 11);
  oled.print(buf, 30, 11);
  oled.print("lx", 70, 11);
  oled.update(); //디스플레이 업데이트(반영)
  delay(100);
}