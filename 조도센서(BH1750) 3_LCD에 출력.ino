#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
BH1750 lightMeter; //BH1750의 이름을 lightMeter으로 설정

void setup() {
  Wire.begin();
  lightMeter.begin();
  lcd.init(); //lcd를 초기화
  lcd.backlight(); //lcd 백라이트 켜기
}
void loop() {
  float lux = lightMeter.readLightLevel(); //lux라는 변수를 만들고 측정값을 저장
  lcd.setCursor(1, 0); //두 번째 칸, 첫 번째 줄로 커서 이동
  lcd.print("Light: ");
  lcd.setCursor(1, 10);
  lcd.print(lux);
  delay(100);
}