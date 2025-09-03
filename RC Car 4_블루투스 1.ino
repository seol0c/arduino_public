#define TXD 4
#define RXD 2
#define a1 5 //모터드라이버의 a와 b(각각 핀 2개)를 변수 설정
#define a2 6
#define b1 9
#define b2 10

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(TXD, RXD);  //이름을 BTSerial로 지정(TXD, RXD)핀 순서로 연결

void setup() {
  BTSerial.begin(9600);   //소프트웨어시리얼 시작(이하 BT)
  pinMode(a1, OUTPUT);   //모터드라이버의 각 핀을 출력모드로 설정
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
}

void loop() {
  if (BTSerial.available()) {         //BT시리얼에서 값 받기
    char cmd = BTSerial.read(); //BT시리얼에서 받은 값 cmd로 변수 설정
    Serial.println(cmd);        //cmd 값을 시리얼 모니터에 출력 후줄바꿈
    if (cmd == 'F') {           //만일 cmd값이 F이면(작은따옴표)
      analogWrite(a1, 200);         //왼쪽바퀴 전진(속도 200)
      analogWrite(a2, 0);
      analogWrite(b1, 200);         //오른쪽바퀴 전진(속도 200)
      analogWrite(b2, 0);
    }
    else if (cmd == 'B') {           //만일 cmd값이 B이면
      analogWrite(a1, 0);
      analogWrite(a2, 200);         //오른쪽바퀴 후진(속도 200)
      analogWrite(b1, 0);
      analogWrite(b2, 200);         //왼쪽바퀴 후진(속도 200)
    }
    else if (cmd == 'L') {
      analogWrite(a1, 0);
      analogWrite(a2, 100);
      analogWrite(b1, 0);
      analogWrite(b2, 0);
    }
    else if (cmd == 'R') {
      analogWrite(a1, 100);
      analogWrite(a2, 0);
      analogWrite(b1, 0);
      analogWrite(b2, 0);
    }
    else if (cmd == 'G') {           //만일 cmd값이 G이면(앞,왼쪽)
      analogWrite(a1, 100);
      analogWrite(a2, 0);
      analogWrite(b1, 200);
      analogWrite(b2, 0);
    }
    else if (cmd == 'I') {           //만일 cmd값이 I이면(앞,오른쪽)
      analogWrite(a1, 200);
      analogWrite(a2, 0);
      analogWrite(b1, 100);
      analogWrite(b2, 0);
    }
    else if (cmd == 'H') {           //만일 cmd값이 H이면(뒤,왼쪽)
      analogWrite(a1, 0);
      analogWrite(a2, 100);
      analogWrite(b1, 0);
      analogWrite(b2, 200);
    }
    else if (cmd == 'J') {           //만일 cmd값이 J이면(뒤,오른쪽)
      analogWrite(a1, 0);
      analogWrite(a2, 200);
      analogWrite(b1, 0);
      analogWrite(b2, 100);
    }
    else {
      analogWrite(a1, 0);
      analogWrite(a2, 0);
      analogWrite(b1, 0);
      analogWrite(b2, 0);
    }
  }
}
