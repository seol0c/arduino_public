int PIR = 7; //인체감지센서 7번핀
int PIRstate = 0; //PIR상태를 초기에 0으로
//PIRstate의 의미를 알기 위하여 스위치_모드변경을 참고하세요.


//LOW 말고 0
//int PIR_val=digi 바로

void setup() {
  pinMode(PIR, INPUT);
  Serial.begin(9600);
}

void loop() {
  int PIR_val = digitalRead(PIR); //PIR 디지털 읽기 값을 PIR_val이라고 설정
  if (PIR_val == HIGH) { //만일 PIR_val값이 있다면(센서 감지)
    if (PIRstate == 0) { //그 상태에서 만일 PIRstate가 0이라면
      Serial.println("motion detected"); //문구 출력 후 줄바꿈
      PIRstate = 1; //PIRstate를 1로 변경
      delay(100);
    } //들여쓰기된 if절의 구조를 잘 확인하세요.
  }
  else { //그렇지 않을 시(PIR_val값이 없는 상태, 센서 미감지)
    if (PIRstate == 1) { //그 상태에서 만일 PIRstate가 1이라면
      Serial.println("motion ended"); //문구 출력 후 줄바꿈
      PIRstate = 0; //PIRstate를 0으로 변경
      delay(100);
    }
  }
}