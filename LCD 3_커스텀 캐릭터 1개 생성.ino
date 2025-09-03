/* 구글에 "custom character"을 검색하면 "LCD Custom Character Generator"가 있습니다.
  구체적인 사이트 주소는 https://maxpromer.github.io/LCD-Character-Creator/ 입니다.
  인터페이스는 I2C를 선택합니다. 데이터타입은 수정이 쉽도록 Hex가 아닌 Binary를 선택합니다. */

/* 사이트에서 코드를 가져오면 수정해야 할 부분이 있습니다.
  1. lcd의 주소는 본인의 lcd 타입에 맞게 수정합니다.
     기본 (0x3F, 16, 2)에서 (0x27, 16, 2)로 수정하였습니다.
  2. lcd.init();  lcd.backlight();
     기본의 lcd.begin;을 위와 같이 수정합니다.
  3. lcd.home()대신 원하는 커서로 이동합니다. lcd.write를 이용하여 커스텀 캐릭터를 출력합니다.*/




///////////////////위의 내용은 부연설명이며, 바로 아래의 코드로 진행




/* 문자를 출력하는 LCD의 한 칸은 또다시 5*8=40개의 작은 픽셀로 이루어져 있습니다.
  이 40개의 픽셀을 원하는 곳만 출력하여 나만의 문자를 만들 수 있습니다. */

/* 아래 코드는 숫자 "1"을 출력한 모습입니다.
  1은 불이 켜지는 곳이고, 0은 불이 꺼지는 곳입니다. 1,0을 바꾸며 간단히 수정할 수 있습니다. */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte customChar[] = { //"customChar"라는 바이너리 그룹 생성
  B00100, //1과 0을 이용하여 한칸을 이루는 40개의 픽셀 제어
  B01100,
  B10100,
  B00100,
  B00100,
  B00100,
  B00100,
  B11111
};

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customChar); //"customChar"를 LCD의 0값에 추가
  lcd.setCursor(1, 0); //두 번째 칸, 첫 번째 줄로 커서 이동
  lcd.write(0); //0값을 출력(커스텀 캐릭터는 print가 아닌 write 이용)
}

void loop() {
}