#define photo 3 //3번 핀을 photo로 설정
#define led 2 //2번 핀을 led로 설정

void setup() {
  Serial.begin(9600);    //시리얼 통신을 시작. 통신 속도는 9600
  pinMode(photo, INPUT); //photo를 입력모드로 설정
  pinMode(led, OUTPUT);  //led를 출력모드로 설정
}

void loop() {
  int val = digitalRead(photo); //photo 디지털 읽기 값을 val이라고 설정
  Serial.println(val);          //시리얼모니터에 val값을 출력 후 줄바꿈
  if (val == 1) {               //만일 val값이 1이면
    digitalWrite(led, 1);       //led HIGH(1) 출력
  }
  else {                        //그렇지 않으면
    digitalWrite(led, 0);       //led LOW(0) 출력
  }
  delay(100);                   //0.1초간 대기
}