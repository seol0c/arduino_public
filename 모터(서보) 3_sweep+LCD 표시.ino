//경보기 코드에 lcd코드를 적당한 장소마다 복사 후 붙여넣기 합니다.

#include <Servo.h> //서보모터 라이브러리 불러오기

Servo myservo; //서보모터의 이름을 지정

int pos = 0; //pos라는 변수 설정
//position을 의미하며, 서보모터의 각도가 pos라는 값만큼 회전시킬 예정

#include <Wire.h> //i2c 통신을 위해 미리 선언된 헤더파일을 불러옴
#include <LiquidCrystal_I2C.h> //lcd 동작을 위한 헤더파일을 불러옴

LiquidCrystal_I2C lcd(0x27, 16, 2); //lcd의 정보 입력
// 사용할 i2C 주소는 0x27, lcd는 16칸, 2줄임을 의미

void setup() {
  myservo.attach(9); //서보모터를 9번핀에 연결
  lcd.init(); //lcd를 초기화
  lcd.backlight(); //lcd 백라이트 켜기
  lcd.setCursor(1, 0); //두 번째 칸, 첫 번째 줄로 커서 이동
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { //pos가 0에서 시작하여 180보다 작거나 같다면 1만큼 더함
    myservo.write(pos); //서보모터의 각도를 pos라는 값으로 변경
    lcd.clear(); //lcd 지우기
    lcd.print(pos);
    delay(100);
  }
  for (pos = 180; pos >= 0; pos -= 1) { //pos가 180에서 시작하여 0보다 크거나 같으면 1씩 뺌
    myservo.write(pos); //서보모터의 각도를 pos라는 값으로 변경
    lcd.clear(); //lcd 지우기
    lcd.print(pos);
    delay(100);
  }
}