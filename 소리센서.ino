int sound = A0;

void setup() {
  Serial.begin(9600); //시리얼 통신을 시작. 통신 속도는 9600
  //아날로그핀은 입력핀이 기본이므로 pinMode를 설정할 필요가 없습니다.
}

void loop() {
  int sound_val = analogRead(sound);
  Serial.print("sound_val= ");
  Serial.println(sound_val);
}