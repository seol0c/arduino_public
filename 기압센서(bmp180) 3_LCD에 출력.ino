#include <Arduino.h>
#include <Wire.h>
#include <BMP180I2C.h>
#include <LiquidCrystal_I2C.h>

BMP180I2C bmp180(0x77);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Wire.begin();
  bmp180.begin();
  bmp180.resetToDefaults();
  bmp180.setSamplingMode(BMP180MI::MODE_UHR);
  lcd.init(); //lcd를 초기화
  lcd.backlight(); //lcd 백라이트 켜기
}

void loop() {
  lcd.setCursor(1, 0); //두 번째 칸, 첫 번째 줄로 커서 이동
  lcd.print(bmp180.readTemperature());
  //값을 읽고 그것을 get하는 방식에서 read로 변경
  //do, while을 통해 측정값을 얻고 bmp.get~을 이용하여 값을 얻는 과정이 길고 복잡하므로 read로 변경
  lcd.print("'C  "); //커서 이동하지 않으면 연달아 작성됨
  lcd.print(bmp180.readPressure()/100); //100으로 나눈 값(hpa)을 출력
  delay(100);
}

/* lcd.print(bmp180.getTemperature(),1); 으로 표시하면 소수점 첫 번째짜리까지 출력됩니다.
  이런 경우 숫자의 크기가 줄어들 때 이전에 LCD에 써있던 흔적이 지워지지 않습니다.
  lcd.clear()의 코드를 이용하여 흔적을 지울 수 있습니다.
  하지만 깜빡임이 발생하므로 빈칸을 삽입하여 안보이게 할 수 있습니다. */