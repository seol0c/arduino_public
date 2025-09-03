int cds = A0; //A0 핀을 cds로 변수 설정
int led = 2; //2번 핀을 led라고 변수 설정

void setup() {
  Serial.begin(9600); //시리얼 통신을 시작. 통신 속도는 9600
  //아날로그핀은 입력핀이 기본이므로 pinMode를 설정할 필요가 없습니다.
  pinMode(led, OUTPUT); //led는 출력으로 설정
}

void loop() {
  int cdsValue = analogRead(cds); //cds아날로그 읽기 값을 cdsValue라고 설정
  Serial.println(cdsValue); //시리얼모니터에 cdsValue값을 출력 후 줄바꿈
  if (cdsValue < 60) { //만일 cdsValue가 60보다 작으면
    digitalWrite(led, HIGH); //LED를 켭니다.
  }
  else { //그렇지 않으면(cdsValue가 60보다 크거나 같으면)
    digitalWrite(led, LOW); //LED를 끕니다.
  }
}