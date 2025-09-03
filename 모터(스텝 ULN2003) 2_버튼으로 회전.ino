/*ULN드라이버를 이용한 스텝모터 제어
  버튼(리미트 스위치)이 눌러졌을 때 스텝모터가 정해진 스텝만큼 회전
  버튼을 아무리 오래 눌러도 1회만 동작 */

#include <Stepper.h>

const int stepsPerRevolution = 200;

#define Button 12
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
//드라이버 IN1,2,3,4를 8,9,10,11번 핀에 연결

int state = 0;

void setup() {
  myStepper.setSpeed(60);
  pinMode(Button, INPUT);
}

void loop() {
  if (digitalRead(Button)) {
    if (state == 0) {           //버튼이 눌려진 상태로 state가 0이라면
      state = 1;                //state 값을 1로 반환(1회만 작동하게 함)
      myStepper.step(stepsPerRevolution);
    }
  }
  else {
    state = 0;        //버튼이 눌러지지 않으면 state 값을 0으로 반환
  }
}