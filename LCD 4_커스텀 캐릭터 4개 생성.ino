#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte customChar1[] = { //"customChar1"라는 바이너리 그룹 생성, 불 모양
  B00000,
  B00010,
  B10110,
  B01101,
  B01110,
  B11111,
  B11111,
  B01110
};

byte customChar2[] = { //"customChar2"라는 바이너리 그룹 생성, 물방울 모양
  B00000,
  B00100,
  B00110,
  B01111,
  B11111,
  B11111,
  B11111,
  B01110
};

byte customChar3[] = { //"customChar3"라는 바이너리 그룹 생성, 해 모양
  B00100,
  B10101,
  B01110,
  B11011,
  B01110,
  B10101,
  B00100,
  B00000
};

byte customChar4[] = { //"customChar4"라는 바이너리 그룹 생성, 달 모양
  B00100,
  B01110,
  B11001,
  B10000,
  B10000,
  B11001,
  B01111,
  B00110
};

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(1, customChar1); //"customChar1"를 LCD의 1값에 추가
  lcd.createChar(2, customChar2); //"customChar2"를 LCD의 2값에 추가
  lcd.createChar(3, customChar3);
  lcd.createChar(4, customChar4);
  lcd.setCursor(1, 0); //두 번째 칸, 첫 번째 줄로 커서 이동
  lcd.write(1); //1값을 출력(커스텀 캐릭터는 print가 아닌 write 이용)
  lcd.write(2); //2값을 출력
  lcd.write(3);
  lcd.write(4);
}

void loop() {
}