#define a1 5 //모터드라이버의 a와 b(각각 핀 2개)를 변수 설정
#define a2 6
#define b1 9
#define b2 10
#define trig 11 //초음파 센서의 11번, 12번 핀을 trig와 echo로 변수 설정
#define echo 12
#define buzzer 2
#define LED 3


void setup() {
  Serial.begin(9600); //시리얼 통신을 시작. 통신 속도는 9600
  pinMode(a1, OUTPUT); //모터드라이버의 각 핀을 출력모드로 설정
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(trig, OUTPUT); //trig를 출력으로 설정
  pinMode(echo, INPUT); //echo를 입력으로 설정
  pinMode(buzzer, OUTPUT); //trig를 출력으로 설정
  pinMode(LED, INPUT); //echo를 입력으로 설정

}



///////////아직부저led안함 아래는
