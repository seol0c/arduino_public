#define LED 8
#include <IRremote.h> //IRremote 라이브러리 사용

IRrecv irrecv(2); //적외선 센서의 이름을 irrecv로 지정하고 2번 핀에 연결
decode_results results; //적외선 수신 번호를 results라는 값에 저장

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  irrecv.enableIRIn(); //IR수신 시작
}

void loop() {
  if (irrecv.decode(&results)) { //적외선 신호를 해석한 경우

    //decode(&results)함수는 수신된 데이터가 문제가 있으면 0을 반환하고 문제가 없는 경우 1을 반환합니다.
    //즉, 정상적으로 신호가 들어온 경우를 뜻합니다.

    Serial.println(results.value, HEX); //수신된 값을 시리얼모니터에 HEX로 출력후 줄바꿈
    if (results.value == 0xFF30CF) { //1을 누르면 LED 점등
      digitalWrite(LED, HIGH);
    }
    else {
      digitalWrite(LED, LOW); //그렇지 않으면 LED 소등
      //적외선 신호를 해석한 경우에 1을 누르지 않는 경우이므로
      //1을 누른 뒤 아무것도 누르지 않으면 LED는 점등 상태로 있음
    }
    irrecv.resume(); //IR 데이터 수신 후 다음 신호 대기(초기화)
  }
  delay(100);
}