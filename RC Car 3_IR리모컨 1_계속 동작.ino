#define a1 5 //모터드라이버의 a와 b(각각 핀 2개)를 변수 설정
#define a2 6
#define b1 9
#define b2 10
#define HighSpeed 255 //빠른 속도의 출력을 255(최대값)으로 설정
#define LowSpeed 180 //느린 속도의 출력을 180으로 설정
#include <IRremote.h> //IRremote 라이브러리 사용

IRrecv irrecv(2); //적외선 센서의 이름을 irrecv로 지정하고 2번 핀에 연결
decode_results results; //적외선 수신 번호를 results라는 값에 저장

void setup() {
  pinMode(a1, OUTPUT); //모터드라이버의 각 핀을 출력모드로 설정
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  irrecv.enableIRIn(); //IR수신 시작
}

void loop() {
  if (irrecv.decode(&results)) { //적외선 신호를 해석한 경우
    switch (results.value) {
      case 0xFF30CF: leftforward(); break; //1을 누르면 좌향전진
      case 0xFF18E7: forward(); break; //2번을 누르면 전진
      case 0xFF7A85: rightforward(); break; //3 누르면 우향전진
      case 0xFF10EF: left(); break; //4 누르면 좌회전
      case 0xFF38C7: stop(); break; //5 누르면 정지
      case 0xFF5AA5: right(); break; //6 누르면 우회전
      case 0xFF42BD: leftback(); break; //7 누르면 좌향후진
      case 0xFF4AB5: back(); break; //8 누르면 후진
      case 0xFF52AD: rightback(); break; //9 누르면 우향후진
    }
    irrecv.resume(); //IR 데이터 수신 후 다음 신호 대기(초기화)
  }
  delay(100);
}

void forward() { //전진
  analogWrite(a1, HighSpeed);
  analogWrite(a2, 0);
  analogWrite(b1, HighSpeed);
  analogWrite(b2, 0);
}

void back() { //후진
  analogWrite(a1, 0);
  analogWrite(a2, HighSpeed);
  analogWrite(b1, 0);
  analogWrite(b2, HighSpeed);
}

void right() { //우회전, 우회전하기 위하여 왼쪽 바퀴 정회전, 오른쪽 바퀴 역회전
  analogWrite(a1, LowSpeed);
  analogWrite(a2, 0);
  analogWrite(b1, 0);
  analogWrite(b2, LowSpeed);
}

void left() { //좌회전, 좌회전하기 위하여 오른쪽 바퀴 정회전, 왼쪽 바퀴 역회전
  analogWrite(a1, 0);
  analogWrite(a2, LowSpeed);
  analogWrite(b1, LowSpeed);
  analogWrite(b2, 0);
}

void rightforward() { //우향직진, 오른쪽으로 틀며 앞으로 나가기 위해 왼쪽 바퀴가 더 빨리 움직임
  analogWrite(a1, HighSpeed);
  analogWrite(a2, 0);
  analogWrite(b1, LowSpeed);
  analogWrite(b2, 0);
}

void rightback() { //우향후진, 오른쪽으로 틀며 뒤로 나가기 위해 왼쪽 바퀴가 더 빨리 움직임
  analogWrite(a1, 0);
  analogWrite(a2, HighSpeed);
  analogWrite(b1, 0);
  analogWrite(b2, LowSpeed);
}

void leftforward() { //좌향직진, 왼쪽으로 틀며 앞으로 나가기 위해 오른쪽 바퀴가 더 빨리 움직임
  analogWrite(a1, LowSpeed);
  analogWrite(a2, 0);
  analogWrite(b1, HighSpeed);
  analogWrite(b2, 0);
}

void leftback() { //좌향직진, 왼쪽으로 틀며 뒤로 나가기 위해 오른쪽 바퀴가 더 빨리 움직임
  analogWrite(a1, 0);
  analogWrite(a2, LowSpeed);
  analogWrite(b1, 0);
  analogWrite(b2, HighSpeed);
}

void stop() { //모든 바퀴 정지
  analogWrite(a1, 0);
  analogWrite(a2, 0);
  analogWrite(b1, 0);
  analogWrite(b2, 0);
}