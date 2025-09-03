#define TXD 4 //모듈의 TXD(송신)를 4번 핀에 연결
#define RXD 2 //모듈의 RXD(수신)를 2번 핀에 연결
#define led 13

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(TXD, RXD);  //이름을 BTSerial로 지정(TXD, RXD)핀 순서로 연결

void setup() {
  Serial.begin(9600);     //시리얼 시작
  BTSerial.begin(9600);         //소프트웨어시리얼 시작(이하 BT시리얼)
  pinMode(led, OUTPUT);
}
void loop() {
  if (BTSerial.available()) {         //BT시리얼에서 값 받기
    char cmd = BTSerial.read(); //BT시리얼에서 받은 값 cmd로 변수 설정
    Serial.println(cmd);        //cmd 값을 시리얼 모니터에 출력 후줄바꿈
    if (cmd == '1') {           //만일 cmd값이 1이면(작은따옴표, 문자열은 ")
      digitalWrite(led, 1);     //led 켜기
    }
    else if (cmd == '0') {
      digitalWrite(led, 0);
    }
  }
}