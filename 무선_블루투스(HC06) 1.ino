/* HC-06(4핀): 슬레이브만 가능. 기본 속도 9600, HC-05는 기본속도 38400
   HC-05(6핀, 보통 HC-06처럼 4핀만 사용): 슬레이브, 마스터(최대 7개 슬레이브 연결-binding) 가능 */

/* AT command(AT 3.0ver) - 시리얼 모니터는 "Both NL & CR"로 설정 - 제조년도에 따라 다를 수 있음
   AT+VERSION 버전 확인
   AT+NAME / 이름을 바꾸고 싶다면 AT+NAME=이름 으로 설정
   AT+PSWD / 비밀번호 바꾸고 싶다면 AT+PSWD="비밀번호" 로 설정. 큰따옴표 적어야 함
   AT+ROLE / 역할을 바꾸고 싶다면 AT+ROLE=0(slave), 1(master), 2(slave-loop)
   AT+UART 통신속도 확인 */

/* AT command(AT 1.8ver) - 시리얼 모니터는 "line ending 없음"으로 설정
   AT+VERSION 버전 확인
   이름을 바꾸고 싶다면 AT+NAME이름 으로 설정
   비밀번호 바꾸고 싶다면 AT+PIN비밀번호 로 설정
   역할을 바꾸고 싶다면 AT+ROLE=S(Slave), M(Master)
   통신속도 바꾸고 싶다면 AT+BAUD1 ~ 8 (1 ~ 8은 1200에서 115200까지) */

/* AT command 이후 휴대폰과 연결하고, 어플로 터미널 등 제어
   아래는 최초 AT 통신만 다룸*/

#define TXD 4 //모듈의 TXD(송신)를 4번 핀에 연결
#define RXD 2 //모듈의 RXD(수신)를 2번 핀에 연결
//4,2번 핀 아니라 3,2나 7,8등 변경 가능

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(TXD, RXD);  //이름을 BTSerial로 지정(TXD, RXD)핀 순서로 연결

void setup() {
  Serial.begin(9600);     //시리얼 시작
  BTSerial.begin(9600);   //소프트웨어시리얼 시작(이하 BT시리얼)
}
void loop() {
  if (BTSerial.available()) {       //BT시리얼에서 값 받기
    Serial.write(BTSerial.read());  //BT시리얼에서 받은 값 시리얼모니터로 전송
  }
  if (Serial.available()) {   //시리얼에서 값 받기
    BTSerial.write(Serial.read());  //시리얼에서 받은 값 BT시리얼로 전송
  }
}
