#define act 12 //액츄에이터(LED 또는 능동부저) 등 12번에 연결

#define trig 8 //트리거 핀 8
#define echo 9 //에코 핀 9, 에코와 트리거는 모든 디지털 핀에 연결 가능

void setup() {
  pinMode(act, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); //딜레이 10us
  digitalWrite(trig, LOW);
  int distance = pulseIn(echo, HIGH) * 170 / 1000; //초음파 공식 끝
  Serial.print("거리:");
  Serial.print(distance); //거리를 시리얼 모니터에 출력
  Serial.println("mm");
  delay(1000); //1초 대기
  if (distance < 100) { //거리 측정값이 100mm미만이면
    digitalWrite(act, HIGH); //액츄에이터(LED 또는 능동부저)에 HIGH신호 출력(켜기)
    delay(100);
  }
  else {  //그렇지 않을 시(거리 측정값이 100mm보다 크거나 같으면)
    digitalWrite(act, LOW); //액츄에이터(LED 또는 능동부저)에 LOW신호 출력(끄기)
    delay(1000); //1초 대기
  }
}