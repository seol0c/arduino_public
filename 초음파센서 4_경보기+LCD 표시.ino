/* 경보기 코드에 lcd코드를 적당한 장소마다 복사 후 붙여넣기 합니다.
   시리얼 통신에 해당하는 코드는 지웁니다. */

#define act 12 //액츄에이터(LED 또는 능동부저) 등 12번에 연결

#define trig 8 //트리거 핀 8
#define echo 9 //에코 핀 9, 에코와 트리거는 모든 디지털 핀에 연결 가능

#include <Wire.h> //i2c 통신을 위해 미리 선언된 헤더파일을 불러옴
#include <LiquidCrystal_I2C.h> //lcd 동작을 위한 헤더파일을 불러옴

LiquidCrystal_I2C lcd(0x27, 16, 2); //lcd의 정보 입력
// 사용할 i2C 주소는 0x27, lcd는 16칸, 2줄임을 의미

void setup() {
  pinMode(act, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  lcd.init(); //lcd를 초기화
  lcd.backlight(); //lcd 백라이트 켜기
}

void loop() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); //딜레이 10us
  digitalWrite(trig, LOW);
  int distance = pulseIn(echo, HIGH) * 170 / 1000; //초음파 공식 끝
  lcd.setCursor(1, 0); //두 번째 칸, 첫 번째 줄로 커서 이동
  lcd.print(distance);
  delay(1000); //1초 대기
  if (distance < 100) { //거리 측정값이 100mm미만이면
    digitalWrite(act, HIGH); //액츄에이터(LED 또는 능동부저)에 HIGH신호 출력(켜기)
    delay(100);
  }
  else {  //그렇지 않을 시(거리 측정값이 100mm보다 크거나 같으면)
    digitalWrite(act, LOW); //액츄에이터(LED 또는 능동부저)에 LOW신호 출력(끄기)
    delay(1000); //1초 대기
  }
}