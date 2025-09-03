void setup() { //주로 초기조건을 선언, 필수적으로 있어야 함
  pinMode(2, OUTPUT); //2번 핀을 출력모드로 설정
  pinMode(3, OUTPUT); //3번 핀을 출력모드로 설정
}

void loop() { //반복함수, 프로그램의 주 내용이 들어가며 필수적으로 있어야 함
  digitalWrite(2, HIGH); //2번 핀 HIGH 출력
  digitalWrite(3, LOW); //3번 핀 LOW 출력
  delay(1000); //1초간 대기
  digitalWrite(2, LOW); //2번 핀 LOW 출력
  digitalWrite(3, HIGH); //3번 핀 HIGH 출력
  delay(1000); //1초간 대기
}