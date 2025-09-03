#define a1 5 //모터드라이버의 a와 b(각각 핀 2개)를 변수 설정
#define a2 6
#define b1 9
#define b2 10
#define HighSpeed 255 //빠른 속도의 출력을 255(최대값)으로 설정
#define LowSpeed 180 //느린 속도의 출력을 180으로 설정

//건전지 소모 등으로 전력이 충분하지 않으면 200 이하로 모터가 돌지 못하고 고주파음이 발생함

void setup() {
  pinMode(a1, OUTPUT); //모터드라이버의 각 핀을 출력모드로 설정
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
}

void loop() {
  forward(); //전진
  delay(1000);
  stop();
  delay(1000);

  back(); //후진
  delay(1000);
  stop();
  delay(1000);

  right(); //우회전
  delay(1000);
  stop();
  delay(1000);

  rightforward(); //우향직진
  delay(1000);
  stop();
  delay(1000);

  rightback(); //우향후진
  delay(1000);
  stop();
  delay(1000);

  left(); //좌회전
  delay(1000);
  stop();
  delay(1000);

  leftforward(); //좌향전진
  delay(1000);
  stop();
  delay(1000);

  leftback(); //좌향후진
  delay(1000);
  stop();
  delay(1000);

}

//아래는 방향 함수

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