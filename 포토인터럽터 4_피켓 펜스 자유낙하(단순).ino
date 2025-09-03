//곧바로 millis()를 호출하는 코드

#define photo 2

int block_event = 0; //포토인터럽터 block 상태 0으로 설정

void setup() {
  pinMode(photo, INPUT);
  Serial.begin(9600);
}

void loop() {
  int photostate = digitalRead(photo); //포토인터럽터 값을 photostate에 저장
  if (photostate == 1) { //포토인터럽터 검출
    if (block_event == 0) { //block 상태가 0이라면
      Serial.println(millis()); //경과 시간 출력
      block_event = 1; //block 상태 1로 변경(경과시간 출력하지 않음)
    }
  }
  else {
    block_event = 0; //포토인터럽터 미검출시 block 상태 0으로 변경
  }
}

/* millis()는 프로그램이 시작한 후부터 측정한 밀리초이며, 약 50일 후 오버플로우됩니다.
  millis ()의 반환 값은 unsigned long 이므로 int 와 같은 작은 자료형으로 산술을 수행하려고하면
  논리 오류가 발생할 수 있습니다.
  signed long 의 최대값의 경우도 unsigned long의 최대값의 절반이기 때문에 오류가 발생할 수 있습니다. */