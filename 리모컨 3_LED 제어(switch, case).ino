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
    switch (results.value) {

      //switch는 변수 값을 case에 지정된 값과 비교합니다.
      //case문의 값이 변수와 같으면 case문에 있는 코드가 실행됩니다.
      //break은 switch를 빠져나오도록 하며, case의 끝에 쓰입니다.
      //break이 없으면 switch문은 break이 나올 때까지(break이 없다면 switch가 끝날 때까지) 다음 문장을 이어서 진행합니다.

      case 0xFF30CF: digitalWrite(LED, HIGH); break; //1을 누르면 LED 점등
      case 0xFF18E7: digitalWrite(LED, LOW) break; //2 누르면 LED 소등
      case 0xFF7A85: break; //3 누르면
      case 0xFF10EF: break; //4 누르면
      case 0xFF38C7: break; //5 누르면
      case 0xFF5AA5: break; //6 누르면
      case 0xFF42BD: break; //7 누르면
      case 0xFF4AB5: break; //8 누르면
      case 0xFF52AD: break; //9 누르면
    }
    irrecv.resume(); //IR 데이터 수신 후 다음 신호 대기(초기화)
  }
  delay(100);
}