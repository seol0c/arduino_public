
#include <Wire.h> //i2c 통신을 위해 미리 선언된 헤더파일을 불러옴
#include <LiquidCrystal_I2C.h> //lcd 동작을 위한 헤더파일을 불러옴

LiquidCrystal_I2C lcd(0x27, 16, 2);


int relay = 2; //2번 핀을 relay로 변수 설정
int PIR = 7; //인체감지센서 7번핀
int PIRstate = 0; //PIR상태를 초기에 0으로
int cds = A0; //A0 핀을 cds로 변수 설정
int delaytime = 8000; //딜레이시간 설정
int limit = 30; //작동 밝기 설정

void setup() {
  pinMode(relay, OUTPUT); //relay를 출력모드로 설정
  pinMode(PIR, INPUT);
  lcd.init(); //lcd를 초기화
  lcd.backlight(); //lcd 백라이트 켜기
  lcd.setCursor(0, 0); //첫 번째 칸, 첫 번째 줄로 커서 이동
  lcd.print("pir:");
  lcd.setCursor(9, 0);
  lcd.print("dly:");
  lcd.setCursor(13, 0);
  lcd.print(delaytime / 1000);
  lcd.setCursor(0, 1); //첫 번째 칸, 두 번째 줄로 커서 이동
  lcd.print("lux:");
  lcd.setCursor(9, 1);
  lcd.print("lim:");
  lcd.setCursor(13, 1);
  lcd.print(limit);
}

void loop() {
  int cdsValue = analogRead(cds); //cds 아날로그 읽기 값을 cdsValue라고 설정
  lcd.setCursor(4, 1);
  lcd.print(cdsValue); //시리얼모니터에 cdsValue값을 출력 후 줄바꿈
  delay(100);
  int PIR_val = digitalRead(PIR); //PIR 디지털 읽기 값을 PIR_val이라고 설정
  if (PIR_val == HIGH) { //만일 PIR_val값이 있다면(센서 감지)
    digitalWrite(relay, HIGH); //relay HIGH 출력
    if (PIRstate == 0) { //그 상태에서 만일 PIRstate가 0이라면
      PIRstate = 1; //PIRstate를 1로 변경
      lcd.setCursor(4, 0);
      lcd.print(PIRstate);
      delay(delaytime);
    }
  }
  else { //그렇지 않을 시(PIR_val값이 없는 상태, 센서 미감지)
    digitalWrite(relay, LOW); //relay LOW 출력
    if (PIRstate == HIGH) { //그 상태에서 만일 PIRstate가 HIGH라면
      PIRstate = 0; //PIRstate를 0으로 변경
      lcd.setCursor(4, 0);
      lcd.print(PIRstate);
    }
  }
}