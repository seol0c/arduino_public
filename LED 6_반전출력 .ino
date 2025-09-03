void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  // HIGH 일경우 LOW로, LOW일 경우 HIGH 로 반전 출력
  digitalWrite(13, !(digitalRead(13)));
  delay(500);
}