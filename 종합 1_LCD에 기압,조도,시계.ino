//1. 기압센서에서 setup 위 라이브러리 가져옴

#include <Arduino.h>
#include <Wire.h>
#include <BMP180I2C.h>
#include <LiquidCrystal_I2C.h>

BMP180I2C bmp180(0x77);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//2. 조도센서에서 setup 위 라이브러리 가져옴. LCD관련 라이브리리는 중복되니 삭제함
#include <BH1750.h>
BH1750 lightMeter;

//3. RTC에서 setup 위 라이브러리 가져옴. LCD관련 라이브리리는 중복되니 삭제함
#include <ThreeWire.h>
#include <RtcDS1302.h>
ThreeWire myWire(4, 5, 2);
RtcDS1302<ThreeWire> Rtc(myWire);

//4. 기압, 조도, RTC에서 setup함수에 들어갈 코드들을 가져옴. 중복되는 것 삭제
void setup() {
  Wire.begin();
  bmp180.begin();
  bmp180.resetToDefaults();
  bmp180.setSamplingMode(BMP180MI::MODE_UHR);
  lightMeter.begin();
  Rtc.Begin();
  lcd.init();
  lcd.backlight();
}

//5. 기압, 조도, RTC에서 loop함수에 들어갈 코드들을 가져옴. 중복되는 것 삭제
//헷갈리지 않게 lcd.print는 마지막에 몰아서 작성
void loop() {
  //기압센서 측정부

  //조도센서 측정부
  float lux = lightMeter.readLightLevel();

  //RTC
  RtcDateTime now = Rtc.GetDateTime();

  //기압센서 출력부
  lcd.setCursor(0, 0); //첫 번째 칸, 첫 번째 줄로 커서 이동
  lcd.print(bmp180.readTemperature());
  //값을 읽고 그것을 get하는 방식에서 read로 변경
  //do, while을 통해 측정값을 얻고 bmp.get~을 이용하여 값을 얻는 과정이 길고 복잡하므로 read로 변경
  lcd.print("'C  "); //커서 이동하지 않으면 연달아 작성됨
  lcd.print(bmp180.readPressure()/100); //100으로 나눈 값(hpa)을 출력

  //RTC 출력부 - 커서 이동 바꾸고 코드 수정
  lcd.setCursor(0, 1); //첫 번째 칸, 두 번째 줄로 커서 이동
  if (now.Hour() < 10) {
    lcd.print("0");
  }
  lcd.print(now.Hour()); //"시간"을 정수 형태로 표시(10보다 작으면 앞에 0 추가)

  lcd.print(":");
  if (now.Minute() < 10) {
    lcd.print("0");
  }
  lcd.print(now.Minute()); //"분"을 정수 형태로 표시(10보다 작으면 앞에 0 추가)

  lcd.print(":");
  if (now.Second() < 10) {
    lcd.print("0");
  }
  lcd.print(now.Second()); //"초"를 정수 형태로 표시(10보다 작으면 앞에 0 추가)
  lcd.print(" "); //커서 이동하지 않으면 연달아 작성됨

  //조도센서 출력부 - 코드 수정
  lcd.print(lux);

  //딜레이 및 클리어 - 클리어 실행시 깜빡이는 현상이 생김, 이를 방지하기 위해 공백을 채울 수 있음
  lcd.print("  ");
  delay(100);  
}