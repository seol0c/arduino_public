int cds = A0; //A0 핀을 cds로 변수 설정
int relay = 2; //2번 핀을 relay로 변수 설정

void setup() {
  Serial.begin(9600); //시리얼 통신을 시작. 통신 속도는 9600
  //아날로그핀은 입력핀이 기본이므로 pinMode를 설정할 필요가 없습니다.
  pinMode(relay, OUTPUT); //relay를 출력모드로 설정
}

void loop() {
  int cdsValue = analogRead(cds); //cds아날로그 읽기 값을 cdsValue라고 설정
  Serial.println(cdsValue); //시리얼모니터에 cdsValue값을 출력 후 줄바꿈
  if (cdsValue < 60) {
    digitalWrite(relay, HIGH);
  }
  else {
    digitalWrite(relay, LOW);
  }
}

//이전 코드와 비교하면 led가 relay로만 바뀝니다. 그 의미에 대해 생각해보세요.