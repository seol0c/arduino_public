int potentiometer = A0; //A0 핀을 potentiometer로 변수 설정
int LED = 3; //3번 핀을 LED로 변수 설정

void setup() {
  pinMode(LED, OUTPUT); //LED를 출력모드로 설정
  //아날로그핀은 입력핀이 기본이므로 pinMode를 설정할 필요가 없습니다.
}

void loop() {
  int AI = analogRead(potentiometer);
  //potentiometer을 통해 받는 값(가변저항)을 AI(Analog Input)이라는 변수로 설정

  /* 가변저항에 저항의 변화가 일어나고 아두이노는 이를 감지합니다.
    입력 핀에 입력될 수 있는 값은 1024가지(0~1023)입니다.
    출력 핀이 출력할 수 있는 값은 256가지(0~255)입니다.(PWM 핀)
    입력된 값을 4로 나눠주면 아날로그 값과 디지털 값의 범위가 같게 됩니다. */

  int Brightness = AI / 4; //AI값을 다시 4로 나눈 것을 Brightness라는 변수로 설정
  analogWrite(LED, Brightness); //아날로그 출력 강도를 Brightness로 설정
}