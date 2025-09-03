#include <Arduino.h> //oled(5V, GND, SCL-A5, SDA-A4)
#include <U8x8lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

#include <LiquidCrystal_I2C.h> //0.96 lcd1602(5V, GND, SCL-A5, SDA-A4)
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <ThreeWire.h> //rtc(5V, GND, CLK-5, DAT-4, RST-2)
#include <RtcDS1302.h>
ThreeWire myWire(4, 5, 2);
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
  Serial.begin(57600); //pc에서 시리얼통신할 경우
  Rtc.Begin(); //rtc 통신 시작
  u8x8.begin(); //oled u8x8통신 시작
  u8x8.setPowerSave(0);
  lcd.init(); //lcd 시작
  lcd.backlight();
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime(); //rtc 시간값을 읽어서 now라는 변수에 저장(한줄이면 됨)

 //oled 출력 시작

  u8x8.setFont(u8x8_font_chroma48medium8_r); //oled 폰트 지정
  u8x8.setCursor(1, 0); //oled 커서 지정(첫 번째 줄)
  u8x8.print("youngchan seol");
  u8x8.setCursor(4, 2); //oled 커서 지정(두 번째 줄)
  if (now.Hour() < 10) {
    u8x8.print("0");
  }
  u8x8.print(now.Hour()); //"시간"을 정수 형태로 표시(10보다 작으면 앞에 0 추가)

  u8x8.print(":");
  if (now.Minute() < 10) {
    u8x8.print("0");
  }
  u8x8.print(now.Minute()); //"분"을 정수 형태로 표시(10보다 작으면 앞에 0 추가)

  u8x8.print(":");
  if (now.Second() < 10) {
    u8x8.print("0");
  }
  u8x8.print(now.Second()); //"초"를 정수 형태로 표시(10보다 작으면 앞에 0 추가)
  u8x8.refreshDisplay(); //refresh, 모두 지우고 덮어쓰기 위함


 //lcd 출력 시작
  lcd.setCursor(1, 0); //lcd 출력, 첫 번째 줄에 문구 표시
  lcd.print("youngchan seol");
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
