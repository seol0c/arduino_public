/*A4988드라이버를 이용한 스텝모터(NEMA) 제어
  버튼(리미트 스위치)이 눌러졌을 때 스텝모터가 정해진 스텝만큼 회전
  버튼을 아무리 오래 눌러도 1회만 동작 */

#define STEP 4    //모터 출력핀을 4번에 연결
#define DIR 3     //모터 방향핀을 3번에 연결
#define Button 5  //버튼(또는 리미트스위치)을 5번에 연결
int state = 0;    //상태와 관련된 변수 생성(1회만 동작하게 하도록 하기 위함)

void setup() {
  pinMode(STEP, OUTPUT);    //모터핀을 출력모드로 설정
  pinMode(DIR, OUTPUT);     //방향핀을 출력 모드로 설정
  digitalWrite(DIR, HIGH);  //방향을 정방향으로 설정(역방향은 LOW)
  pinMode(Button, INPUT);   //버튼을 입력 모드로 설정
}

void loop() {
  if (digitalRead(Button)) {          //만일 버튼이 눌러져있다면
    if (state == 0) {                 //그 상태에서 state가 0이라면
      state = 1;                      //state를 1로 반환
      for (int x = 0; x < 200; x++) { //아래 코드는 특정 스텝을 이동하는 코드
        digitalWrite(STEP, HIGH);
        delayMicroseconds(700);
        digitalWrite(STEP, LOW);
        delayMicroseconds(700);
      }
    }
  }
  else {                              //버튼이 눌러지지 않았다면
    digitalWrite(STEP, LOW);          //모터 정지
    digitalWrite(STEP, LOW);
    state = 0;                        //state를 0으로 반환
  }
}