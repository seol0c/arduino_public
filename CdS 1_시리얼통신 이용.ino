/* CdS는 한쪽 다리에 5V, 한쪽 다리에 저항을 연결하고 GND에 연결합니다.
  저항에 연결된 다리에 신호핀을 연결하고 아두이노 보드의 아날로그 핀에 연결합니다. */

int cds = A0; //A0 핀을 cds로 변수 설정

void setup() {
  Serial.begin(9600); //시리얼 통신을 시작. 통신 속도는 9600
  //아날로그핀은 입력핀이 기본이므로 pinMode를 설정할 필요가 없습니다.
}

/* 시리얼 통신은 아두이노가 받아들인 센서값이나 동작 중인 값을
   사용자가 실시간으로 볼 수 있도록 아두이노와 컴퓨터가 통신하는 것입니다. */

void loop() {
  int cdsValue = analogRead(cds); //cds 아날로그 읽기 값을 cdsValue라고 설정
  //매번 측정된 값을 새롭게 바꾸어야 하므로 loop 안에서 int로 변수 설정
  Serial.println(cdsValue); //시리얼모니터에 cdsValue값을 출력 후 줄바꿈
  delay(500); //0.5초간 대기
}