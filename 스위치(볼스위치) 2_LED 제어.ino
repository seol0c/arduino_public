int Button = 2;
int led = 3;

void setup() {
  Serial.begin(9600);
  pinMode(Button, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int Button_val = digitalRead(Button); //Button의 디지털 읽기 값을 Button_val이라고 부름(변수 설정)
  Serial.println(Button_val); //Button_val의 값을 시리얼모니터에 출력 후 줄바꿈
  if (Button_val == 0) { //만일 Button_val값이 0이면(바로 선 상태)
    digitalWrite(led, HIGH); //led를 켜라
  }
  else { //그렇지 않으면(거꾸로 기울여져서 1이 된 상태)
    digitalWrite(led, LOW); //led를 꺼라
  }
  delay(100);
}