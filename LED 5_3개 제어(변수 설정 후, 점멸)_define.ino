int led1 = 6; //6번 핀이라고 부르지 않고 앞으로 led1라고 부름(변수 설정)
int led2 = 7; //7번 핀이라고 부르지 않고 앞으로 led2라고 부름(변수 설정)
int led3 = 8; //8번 핀이라고 부르지 않고 앞으로 led2라고 부름(변수 설정)

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

/* int와 define의 차이
  #define은 '매크로'라고도 부릅니다.
  #define LED 3 이라고 작성하면
  작성한 코드에서 모든 LED를 3으로 바꾸어 보드에 업로드합니다.
  업로드 될 때 보드에 LED가 들어가지 않게 됩니다.

  int는 변수로서 메모리(2바이트)를 할당받고 자리를 차지하게 됩니다.
  int LED=3; 이라고 작성하면
  아두이노 보드에는 LED라는 변수가 그대로 업로드되고
  LED가 나올 때마다 보드에서 LED가 어떤 값인지 찾게 됩니다.

  계속 값을 받거나, 값이 변하는 경우(센서를 통한 측정)에는 int를 써야하며
  메모리가 할당되지 않으므로 값이 고정된 상태인 경우(핀 번호) define이 유리합니다.
  
  (ppt 참고하기) */