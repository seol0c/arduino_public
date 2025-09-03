int led = 2; //2번 핀이라고 부르지 않고 앞으로 led라고 부름(변수 설정)
int sound = A0;

void setup() {
  Serial.begin(9600); //시리얼 통신을 시작. 통신 속도는 9600
  pinMode(led, OUTPUT); //led를 입력모드로 설정
}

void loop() {
  int sound_val = analogRead(sound);
  Serial.print("sound_val= ");
  Serial.println(sound_val);
  if (sound_val > 150) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  delay(100);
}