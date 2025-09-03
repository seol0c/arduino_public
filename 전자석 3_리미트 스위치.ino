int electromagnet = 2;
int sw = 3;

void setup() {
  pinMode(electromagnet, OUTPUT);
  pinMode(sw, INPUT);
}

void loop() {
  digitalWrite(electromagnet, HIGH); //처음상태에는 전자석을 HIGH
  if (digitalRead(sw) == 0) {        //만일 스위치가 0이면(눌린 상태)
    digitalWrite(electromagnet, LOW); //전자석을 LOW
    delay(3000);                    //3초간 대기
  }
}