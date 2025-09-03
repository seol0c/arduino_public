/* 가변저항의 다리는 3개 입니다.
   양끝을 5V와 GND에 연결하고 다운데를 A0 핀에 연결합니다. */


int potentiometer = A0; //A0 핀을 potentiometer로 변수 설정

void setup() {
  Serial.begin(9600); //시리얼 통신을 시작. 통신 속도는 9600
  //아날로그핀은 입력핀이 기본이므로 pinMode를 설정할 필요가 없습니다.
}

/* 시리얼 통신은 아두이노가 받아들인 센서값이나 동작 중인 값을
   사용자가 실시간으로 볼 수 있도록 아두이노와 컴퓨터가 통신하는 것입니다. */

void loop() {
  int AI = analogRead(potentiometer);
  //potentiometer을 통해 받는 값(가변저항)을 AI(Analog Input)이라는 변수로 설정
  Serial.println(AI); //시리얼모니터에 AI값을 출력 후 줄바꿈
  delay(500); //0.5초간 대기
}