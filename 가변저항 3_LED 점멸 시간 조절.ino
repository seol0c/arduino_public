int potentiometer = A0; //A0 핀을 potentiometer로 변수 설정
int LED = 3; //3번 핀을 LED로 변수 설정

void setup() {
  pinMode(LED, OUTPUT); //LED를 출력모드로 설정
  //아날로그핀은 입력핀이 기본이므로 pinMode를 설정할 필요가 없습니다.
  Serial.begin(9600);
}

void loop() {
  int DelayTime = analogRead(potentiometer);
  //potentiometer을 통해 받는 값(가변저항)을 DelayTime이라는 변수로 설정
  Serial.println(DelayTime); //시리얼모니터에 DelayTime값을 출력 후 줄바꿈
  digitalWrite(LED, HIGH);
  delay(DelayTime); //LED가 켜지고 기다리는 시간을 DelayTime만큼으로 함
  digitalWrite(LED, LOW);
  delay(DelayTime); //LED가 꺼지고 기다리는 시간을 DelayTime만큼으로 함
}

/* 가변저항의 다이얼을 돌려 저항을 작게 할수록 DelayTime이 작아집니다.
  이때 LED가 어떻게 될지 먼저 생각해보고 코드를 실행해봅시다. */