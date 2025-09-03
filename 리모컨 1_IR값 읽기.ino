//IRremote 라이브러리 다운로드

#include <IRremote.h> //IRremote 라이브러리 사용

IRrecv irrecv(2); //적외선 센서의 이름을 irrecv로 지정하고 2번 핀에 연결
//어느 핀에 연결해도 상관 없음
decode_results results; //적외선 수신 번호를 results라는 값에 저장

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); //IR수신 시작
}

void loop() {
  if (irrecv.decode(&results)) { //적외선 신호를 해석한 경우

    //decode(&results)함수는 수신된 데이터가 문제가 있으면 0을 반환하고 문제가 없는 경우 1을 반환합니다.
    //즉, 정상적으로 신호가 들어온 경우를 뜻합니다.

    Serial.println(results.value, HEX); //수신된 값을 시리얼모니터에 HEX로 출력후 줄바꿈
    irrecv.resume(); //IR 데이터 수신 후 다음 신호 대기(초기화)
  }
  delay(100);
}

/* 리모컨 읽기 결과
  FFA25D / CH-
  FF629D / CH
  FFE21D / CH+
  FF22DD / <<
  FF02FD / >>
  FFC23D / >
  FFE01F / -
  FFA857 / +
  FF906F / EQ
  FF6897 / 0
  FF9867 / 100+
  FFB04F / 200+
  FF30CF / 1
  FF18E7 / 2
  FF7A85 / 3
  FF10EF / 4
  FF38C7 / 5
  FF5AA5 / 6
  FF42BD / 7
  FF4AB5 / 8
  FF52AD / 9
  FFFFFFFF / 같은 값을 계속 누르는 경우
*/