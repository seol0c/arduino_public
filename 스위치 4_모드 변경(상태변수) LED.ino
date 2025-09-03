#define LED 2 //2번 핀을 LED로 설정
#define Button 7 //7번 핀을 Button으로 설정
int state = 0; //상태와 관련된 변수 생성(1회만 동작하게 하도록 하기 위함)

void setup() {
  pinMode(Button, INPUT); //Button을 입력모드로 설정
  pinMode(LED, OUTPUT); //LED를 출력모드로 설정
}

void loop() {
  if (digitalRead(Button) == 1 && state == 1) { //만일 버튼이 눌러져있고, state값이 1이면
    state = 0; //state를 0으로 정하기
    delay(1000); //1초간 대기
  }
  if (digitalRead(Button) == 1 && state == 0) { //만일 버튼이 눌러져있고, state값이 0이면
    state = 1; //state를 1로 정하기
    delay(1000); //1초간 대기
  }
  if (state == 1) { //만일 state 값이 1이면
    digitalWrite(LED, HIGH); //LED를 켭니다.
  }
  else { //그렇지 않으면(state 값이 1이 아니면)
    digitalWrite(LED, LOW); // LED를 끕니다.
  }
}