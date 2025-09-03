


//최종 수정 후 테스트 해보지는 않았음
//잘 작동될 것으로 생각은 됨





#define a1 5 //모터드라이버의 a와 b(각각 핀 2개)를 변수 설정
#define a2 6
#define b1 9
#define b2 10
#define leftLineSensor 7 //라인센서 왼쪽을 7번핀에 연결
#define rightLineSensor 8 //라인센서 왼쪽을 8번핀에 연결

void setup() {
  pinMode(a1, OUTPUT); //모터드라이버의 각 핀을 출력모드로 설정
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(leftLineSensor, INPUT); //라인센서를 입력모드로 설정
  pinMode(rightLineSensor, INPUT);
}

void loop() {
  //변수 값이 길어 헷갈리므로 다른 변수로 설정
  int LL = digitalRead(leftLineSensor);
  int RL = digitalRead(rightLineSensor);

  if (!LL && !RL) { //둘 다 라인을 감지하지 않으면 직진
    forward();
  }
  else if (LL && !RL) { //왼쪽 라인 감지 시 좌회전
    left();
  }
  else if (!LL && RL) { //오른쪽 라인 감지 시 우회전
    right();
  }
  else if (LL && RL) { //양쪽 라인 감지 시 정지
    stop();
  }
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

void right() { //우회전하기 위하여 왼쪽 바퀴 정회전, 오른쪽 바퀴 역회전
  analogWrite(a1, LowSpeed);
  analogWrite(a2, 0);
  analogWrite(b1, 0);
  analogWrite(b2, LowSpeed);
}

void left() { //좌회전하기 위하여 오른쪽 바퀴 정회전, 왼쪽 바퀴 역회전
  analogWrite(a1, 0);
  analogWrite(a2, LowSpeed);
  analogWrite(b1, LowSpeed);
  analogWrite(b2, 0);
}

void stop() { //모든 바퀴 정지
  analogWrite(a1, 0);
  analogWrite(a2, 0);
  analogWrite(b1, 0);
  analogWrite(b2, 0);
}