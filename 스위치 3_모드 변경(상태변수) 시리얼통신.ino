#define Button 7 //7번 핀을 Button으로 설정
int state = 0; //상태와 관련된 변수 생성(1회만 동작하게 하도록 하기 위함)

/* 스위치는 버튼을 누르고 있을 때만 1이 출력됩니다.
  상태와 관련된 새로운 변수를 만들어서 스위치에 1이 출력될 때마다 값을 바꾸게 하면
  누를 때마다 LED가 켜지고 꺼지게 할 수 있습니다.
  계속 값이 달라져야 하고 아두이노에서 state라는 변수 자체를 계속 살펴봐야 하므로 int로 변수 설정합니다. */

void setup() {
  pinMode(Button, INPUT); //Button을 입력모드로 설정
  Serial.begin(9600); //시리얼 통신을 시작. 통신 속도는 9600
}

void loop() {
  if (digitalRead(Button) == 1 && state == 1) { //만일 버튼 값이 1이고, state값이 1이면
    //'&&'의 의미는 '두 가지 조건을 모두 만족할 때'입니다.
    //만일(if)의 상황에서는 =도 두개, &도 두개를 사용합니다.
    state = 0; //state를 0으로 정하기
    delay(500); //0.5초간 대기
  }
  if (digitalRead(Button) == 1 && state == 0) { //만일 버튼 값이 1이고, state값이 0이면
    state = 1; //state를 1로 정하기
    delay(500); //0.5초간 대기
  }
  Serial.println(state); //시리얼모니터에 state값을 출력 후 줄바꿈
  delay(500); //0.5초간 대기
}