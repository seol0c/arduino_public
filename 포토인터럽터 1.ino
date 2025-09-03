/* 포토인터럽터는 CdS와 사용 방법이 유사합니다.
  장애물 감지 여부를 이용하여 스위치로 사용할 수 있습니다.
  실생활에서는 객실 출입키, 전자도어락 잠금상태 확인 등에 쓰입니다. */

#define photo 3 //3번 핀을 photo로 설정

void setup() {
  Serial.begin(9600); //시리얼 통신을 시작. 통신 속도는 9600
  pinMode(photo, INPUT); //photo를 입력모드로 설정
}

void loop() {
  int val = digitalRead(photo); //photo 디지털 읽기 값을 val이라고 설정
  Serial.println(val);       //시리얼모니터에 val값을 출력 후 줄바꿈
  delay(100);                //0.1초간 대기
}