


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

//if절이 길어서 중괄호{}를 빼먹는 실수가 많음

void loop() {
  if (!digitalRead(leftLineSensor) && !digitalRead(rightLineSensor)) { //둘 다 라인을 감지하지 않으면 직진
    analogWrite(a1, 200);
    analogWrite(a2, 0);
    analogWrite(b1, 200);
    analogWrite(b2, 0);
  }
  else if (digitalRead(leftLineSensor) && !digitalRead(rightLineSensor)) { //왼쪽 라인 감지 시 왼쪽 역회전 오른쪽 정회전
    analogWrite(a1, 0);
    analogWrite(a2, 200);
    analogWrite(b1, 200);
    analogWrite(b2, 0);
  }
  else if (!digitalRead(leftLineSensor) && digitalRead(rightLineSensor)) { //오른쪽 라인 감지 시 왼쪽 정회전 오른쪽 역회전
    analogWrite(a1, 200);
    analogWrite(a2, 0);
    analogWrite(b1, 0);
    analogWrite(b2, 200);
  }
  else if (digitalRead(leftLineSensor) && digitalRead(rightLineSensor)) { //양쪽 라인 감지 시 정지
    analogWrite(a1, 0);
    analogWrite(a2, 0);
    analogWrite(b1, 0);
    analogWrite(b2, 0);
  }
}