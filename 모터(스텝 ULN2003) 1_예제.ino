#include <Stepper.h>   //스텝모터 라이브러리 불러오기

int steps = 2048;     //360도 회전: 2048, step값을 2048(한바퀴)로 설정

Stepper myStepper(steps, 8, 9, 10, 11); //모터 세팅

void setup() {
  myStepper.setSpeed(10); //모터 스피드 10
}

void loop() {
  myStepper.step(steps / 4); //모터를 steps값만큼 움직임
  delay(1000);            //1초 대기
}