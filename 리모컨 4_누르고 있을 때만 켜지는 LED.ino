





//작성중









#define LED1 3
#define LED2 4
#define LED3 5
#define LED4 6
#include <IRremote.h> //IRremote 라이브러리 사용

IRrecv irrecv(2); //적외선 센서의 이름을 irrecv로 지정하고 2번 핀에 연결
decode_results results; //적외선 수신 번호를 results라는 값에 저장

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  irrecv.enableIRIn(); //IR수신 시작
}

int te = 0;

int sw(int val) {
  switch (val) {
    case 0xFF30CF: digitalWrite(LED1, HIGH); break; //1 누르면 LED1 점등
      te = val;
      break;
  }
}

void loop() {
  if (irrecv.decode(&results)) { //적외선 신호를 해석한 경우
    Serial.println(results.value, HEX); //수신된 값을 시리얼모니터에 HEX로 출력후 줄바꿈
    sw (results.value);
    if (results.value == 0xFFFFFFFF) {
      sw(te);
    }
  }
  switch (results.value) {
    case 0xFF18E7: digitalWrite(LED2, HIGH); break; //2 누르면 LED2 점등
    case 0xFF7A85: digitalWrite(LED3, HIGH); break; //3 누르면 LED3 점등
    case 0xFF10EF: digitalWrite(LED4, HIGH); break; //4 누르면 LED4 점등
    case 0xFF38C7:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW); break; //5 누르면 모두 소등
    case 0xFF5AA5: break; //6 누르면
    case 0xFF42BD: break; //7 누르면
    case 0xFF4AB5: break; //8 누르면
    case 0xFF52AD: break; //9 누르면
  }
  irrecv.resume(); //IR 데이터 수신 후 다음 신호 대기(초기화)
}
