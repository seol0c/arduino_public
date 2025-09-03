


//최종 수정 후 테스트 해보지는 않았음
//잘 작동될 것으로 생각은 됨





#define a1 5 //모터드라이버의 a와 b(각각 핀 2개)를 변수 설정
#define a2 6
#define b1 9
#define b2 10
#define trig 11 //초음파 센서의 11번, 12번 핀을 trig와 echo로 변수 설정
#define echo 12
#define HighSpeed 255 //빠른 속도의 출력을 255(최대값)으로 설정
#define LowSpeed 200 //느린 속도의 출력을 200으로 설정


void setup() {
  Serial.begin(9600); //시리얼 통신을 시작. 통신 속도는 9600
  //테스트가 끝나면 시리얼 통신은 필요 없음(용량, 전력 차지)
  pinMode(a1, OUTPUT); //모터드라이버의 각 핀을 출력모드로 설정
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(trig, OUTPUT); //trig를 출력으로 설정
  pinMode(echo, INPUT); //echo를 입력으로 설정
}

void loop() {
  digitalWrite(trig, HIGH); //trig에서 HIGH 신호 출력
  delayMicroseconds(10); //10마이크로초 대기
  digitalWrite(trig, LOW); //trig에서 LOW 신호 출력
  int distance = pulseIn(echo, HIGH) * 170 / 1000; //10,000으로 나누면 cm로 구할 수 있음
  Serial.print(distance); //거리값을 출력
  Serial.println("mm"); //문자 "mm"값을 출력후 줄바꿈

  forward();
  delay(100);

  if (distance < 200) { //거리가 200mm미만 이면
    back(200);
    delay(1000); //후진을 1초간 유지(1초간 후진)
    left(200);
    delay(1000); //1초간 좌회전
    stop(); //초음파센서의 전력 확보를 위해 잠시 멈춤
    delay(100)
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