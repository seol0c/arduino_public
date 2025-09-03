/* 릴레이는 컨트롤이 가능한 스위치의 일종입니다.
  작은 전압으로 큰 전압을 조절할 수 있습니다.
  아두이노의 작은 전압으로 가정에서 사용하는 전기 장치를 제어합니다. */

int relay = 2; //2번 핀을 relay로 변수 설정

void setup() {
  pinMode(relay, OUTPUT); //relay를 출력모드로 설정
}

void loop() {
  digitalWrite(relay, HIGH); //relay HIGH 출력
  delay(1000); //1초간 대기
  digitalWrite(relay, LOW); //relay LOW 출력
  delay(1000); //1초간 대기
}

/* 위 코드는 릴레이를 제어하는 코드일 뿐입니다.
  단지 릴레이에 LED를 연결하면 LED의 전원이 제어되고
  다른 모듈을 연결하면 해당 모듈의 전원이 제어되는 것입니다. */