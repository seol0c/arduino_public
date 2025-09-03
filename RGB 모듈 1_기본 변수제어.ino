/* led 3개 제어하는 코드를 그대로 사용하였습니다.
  저항이 내장되어 있어 단순하게 출력핀만 연결하여 사용할 수 있습니다.
  이처럼 센서나 led 등에 저항, 콘덴서 등을 연결하여 하나의 덩어리를 만든 것을 모듈이라고 합니다.  */

int led1 = 11; //11번 핀이라고 부르지 않고 앞으로 led1라고 부름(변수 설정)
int led2 = 12; //12번 핀이라고 부르지 않고 앞으로 led2라고 부름(변수 설정)
int led3 = 13; //13번 핀이라고 부르지 않고 앞으로 led2라고 부름(변수 설정)

void setup() { //주로 초기조건을 선언, 필수적으로 있어야 함
  pinMode(led1, OUTPUT); //led1을 출력모드로 설정
  pinMode(led2, OUTPUT); //led2을 출력모드로 설정
  pinMode(led3, OUTPUT); //led3을 출력모드로 설정
}

void loop() { //반복함수, 프로그램의 주 내용이 들어가며 필수적으로 있어야 함
  digitalWrite(led1, HIGH); //led1 HIGH 출력
  digitalWrite(led2, LOW); //led2 LOW 출력
  digitalWrite(led3, LOW); //led3 LOW 출력
  delay(1000); //1초간 대기
  digitalWrite(led1, LOW); //led1 LOW 출력
  digitalWrite(led2, HIGH); //led2 HIGH 출력
  digitalWrite(led3, LOW); //led3 LOW 출력 - 이미 LOW 상태이므로 이 코드는 없어도 됨
  delay(1000); //1초간 대기
  digitalWrite(led1, LOW); //led1 LOW 출력 - 이미 LOW 상태이므로 이 코드는 없어도 됨
  digitalWrite(led2, LOW); //led2 LOW 출력
  digitalWrite(led3, HIGH); //led3 HIGH 출력
  delay(1000); //1초간 대기
}