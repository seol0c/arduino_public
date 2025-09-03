int led1 = 2; //2번 핀이라고 부르지 않고 앞으로 led1라고 부름(변수 설정)
int led2 = 3; //3번 핀이라고 부르지 않고 앞으로 led2라고 부름(변수 설정)

/* 변수 설정을 하면 수정이 필요한 경우 위의 핀 번호만 바꾸면 아래의 코드를 수정할 필요가 없어 편리합니다.
  또한 코드가 복잡해질수록 어떤 모듈을 제어하고 있는지 구분하기 쉬워집니다. */

void setup() { //주로 초기조건을 선언, 필수적으로 있어야 함
  pinMode(led1, OUTPUT); //led1을 출력모드로 설정
  pinMode(led2, OUTPUT); //led2를 출력모드로 설정
}

void loop() { //반복함수, 프로그램의 주 내용이 들어가며 필수적으로 있어야 함
  digitalWrite(led1, HIGH); //led1 HIGH 출력
  digitalWrite(led2, LOW); //led2 LOW 출력
  delay(1000); //1초간 대기
  digitalWrite(led1, LOW); //led1 LOW 출력
  digitalWrite(led2, HIGH); //led2 HIGH 출력
  delay(1000); //1초간 대기
}

/* 코드가 완성된 후 2,3번 핀을 6,7번 핀으로 옮겨봅시다.
  무엇만 변경하면 정상적으로 작동하게 될까요? */