#include <Wire.h> //i2c 통신을 위해 미리 선언된 헤더파일을 불러옴
#include <LiquidCrystal_I2C.h> //lcd 동작을 위한 헤더파일을 불러옴

LiquidCrystal_I2C lcd(0x27, 16, 2); //lcd의 정보 입력
// 사용할 i2C 주소는 0x27, lcd는 16칸, 2줄임을 의미

void setup() {
  lcd.init(); //lcd를 초기화
  lcd.backlight(); //lcd 백라이트 켜기
  //lcd는 문자를 표시하기 전에 먼저 커서를 옮겨놓아야 함
  //(칸, 줄)로 표시하며 첫 번째 줄, 첫 번째 칸을 0,0으로 지정함
  lcd.setCursor(1, 0); //두 번째 칸, 첫 번째 줄로 커서 이동
  lcd.print("Hello, world!!");
  lcd.setCursor(4, 1);
  lcd.print("Arduino!");
  delay(2000); //2초 대기
  lcd.clear(); //lcd 지우기
  lcd.setCursor(4, 0); //다음의 문구 작성
  lcd.print("Gwangju!");
  lcd.setCursor(5, 1);
  lcd.print("Korea!");
}

void loop() { //반복하지 않더라도 필수함수로 꼭 적어줘야 함
} //반복하지 않으면 마지막 모습에서 변하지 않음