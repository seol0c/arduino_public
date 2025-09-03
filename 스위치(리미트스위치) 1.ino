/* 내장된 함수 Switch와 충돌하므로 Button이라고 변수 설정 해줍니다.
  마우스 클릭에 사용되는 리미티드 스위치는 정상상태에서 1, 눌린 상태에서 0의 값을 표현합니다.
  pull up 이나 pull down이 필요없이 곧바로 신호를 받아들입니다. */

int Button = 2;

void setup() {
  Serial.begin(9600);
  pinMode(Button, INPUT);
}

void loop() {
  int Button_val = digitalRead(Button); //Button의 디지털 읽기 값을 Button_val이라고 부름(변수 설정)
  Serial.println(Button_val);     //Button_val의 값을 시리얼모니터에 출력 후 줄바꿈
  delay(100);
}