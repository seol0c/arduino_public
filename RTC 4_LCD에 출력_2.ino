#include <LiquidCrystal_I2C.h> //0.96 lcd 1602
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <ThreeWire.h> //Rtc
#include <RtcDS1302.h>
ThreeWire myWire(4, 5, 2);
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
  Rtc.Begin(); //rtc 통신 시작
  lcd.init(); //lcd 시작
  lcd.backlight(); //백라이트 켜기
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime(); //rtc 시간값을 읽어서 now라는 변수에 저장(한줄이면 됨)
  //lcd 출력 시작
  lcd.setCursor(2, 0); //lcd 출력, 첫 번째 줄에 문구 표시
  lcd.print("Time is Gold");
  lcd.setCursor(4, 1); //lcd 출력, 두 번째 줄에 시간 표시(oled와 동일, u8x8만 lcd로 변경)
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
  delay(1000);
}