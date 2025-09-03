#define trig 8 //트리거 핀 8
#define echo 9 //에코 핀 9, 에코와 트리거는 모든 디지털 핀에 연결 가능

void setup() {
  pinMode(trig, OUTPUT); //trig를 출력으로 설정
  pinMode(echo, INPUT); //echo를 입력으로 설정
  Serial.begin(9600); //시리얼 통신을 시작. 통신 속도는 9600
}

void loop() {
  //loop되며 계속 거리를 구하므로 처음 LOW상태로 두지 않음(첫 값은 버림)
  digitalWrite(trig, HIGH); //trig에서 HIGH 신호 출력
  delayMicroseconds(10); //10마이크로초 대기
  digitalWrite(trig, LOW); //trig에서 LOW 신호 출력

  int distance = pulseIn(echo, HIGH) * 170 / 1000; //10,000으로 나누면 cm로 구할 수 있음

  Serial.print("거리: ");
  Serial.print(distance); //거리값을 출력
  Serial.println("mm"); //문자 "mm"값을 출력후 줄바꿈
  delay(100);
}

//duration이라는 변수를 만들지 않고 곧바로 distance 공식에 집어넣음.
//distance라는 변수를 만들며 바로 공식 전개