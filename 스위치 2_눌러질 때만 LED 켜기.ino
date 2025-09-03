#define LED 2 //2번 핀을 LED로 설정
#define Button 7 //7번 핀을 Button으로 설정

void setup() {
  pinMode(Button, INPUT); //Button을 입력모드로 설정
  pinMode(LED, OUTPUT); //LED를 출력모드로 설정
}

void loop() {
  if (digitalRead(Button) == HIGH) { //만일 Button을 통해 받은 값이 "HIGH"이면
    digitalWrite(LED, HIGH); //LED를 켭니다.
  } else { //그렇지 않으면(Button을 통해 받은 값이 "HIGH"가 아니면)
    digitalWrite(LED, LOW); //LED를 끕니다.
  }
}

//1번 예제처럼 digitalRead(Button)을 다른 변수로 설정하지 않고 그대로 작성하였습니다.