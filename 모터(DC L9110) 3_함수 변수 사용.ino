#define a1 5 //모터드라이버의 a와 b(각각 핀 2개)를 변수 설정
#define a2 6
#define b1 9
#define b2 10

void setup() {
  pinMode(a1, OUTPUT); //모터드라이버의 각 핀을 출력모드로 설정
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
}

void loop() {
  forward(200); //forward 함수 실행. 변수인 속도는 200
  delay(1000);
  back(200);
  delay(1000);
}

void forward(int Speed) {
  analogWrite(a1, Speed);
  analogWrite(a2, 0);
  analogWrite(b1, Speed);
  analogWrite(b2, 0);
}

void back(int Speed) {
  analogWrite(a1, 0);
  analogWrite(a2, Speed);
  analogWrite(b1, 0);
  analogWrite(b2, Speed);
}