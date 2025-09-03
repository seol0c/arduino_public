#include <Servo.h>    //서보모터 라이브러리 불러오기

Servo myservo;        //서보모터의 이름을 지정

void setup() {
  myservo.attach(9);  //서보모터를 9번핀에 연결
}

void loop() {         //서보모터는 각도 0~180도까지 움직일 수 있습니다.
  myservo.write(0);   //서보모터 각도를 0도로 변경
  delay(1000);        //1초 대기
  myservo.write(90);
  delay(1000);
  myservo.write(180);
  delay(1000);
}