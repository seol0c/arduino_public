int electromagnet = 2;
int photo = 3;

void setup() {
  pinMode(electromagnet, OUTPUT);
  pinMode(photo, INPUT);
}

void loop() {
  digitalWrite(electromagnet, HIGH); //처음상태에는 전자석을 HIGH
  if (digitalRead(photo) == 1) {    //만일 포토인터럽터에 장애물이 감지되면
    digitalWrite(electromagnet, LOW); //전자석을 LOW
    delay(3000);                    //3초간 대기
  }
}