//5611A 기준 아래 DP부터 왼쪽으로 4,5,6,7, 위는 왼쪽으로 8,9,10,11, 가운데 GND 연결


void setup() {  //4번 부터 11번 핀까지 모두 출력모드로 설정
  for (int LED_Pin = 4; LED_Pin <= 11; LED_Pin++) {
    pinMode(LED_Pin, OUTPUT);
  }
}

/* 함수를 미리 설정해두고 필요할 때마다 꺼내쓰면 코드가 더 간결해집니다.
  예를 들어 printnumber라는 함수를 만들어 놓고 휴대폰 번호를 작성한다면
  printnumber(0);
  printnumber(1);
  printnumber(0);
  이런 식으로 반복되는 숫자를 간결하게 쓸 수 있습니다. */

/* HIGH와 LOW를 1,0으로 표현할 수 있습니다.
  간결하지만 의미 파악이 힘들기 때문에 평소에 잘 사용하지 않습니다.
  하지만 여러 LED를 동시에 제어하는 경우 1,0으로 표현하는 게 더 유리할 수도 있습니다. */

void printnumber(int number) {  //printnumber라는 함수 생성, number의 값을 변수로서 동작하는 함수
  for (int i = 4; i <= 11; i++) { //i번 핀을 4에서 시작하여 11보다 작거나 같다는 게 참인 경우 1씩 더하며 반복
    digitalWrite(i, LOW); //i번 핀에 LOW 신호를 출력함. 즉, 4~11의 핀을 끄게 됨
  }
  if (number == 0) {    digitalWrite(5, 1);    digitalWrite(6, 1);    digitalWrite(7, 1);    digitalWrite(8, 1);    digitalWrite(9, 1);    digitalWrite(10, 1);  }
  if (number == 1) {    digitalWrite(5, 1);    digitalWrite(8, 1);  }
  if (number == 2) {    digitalWrite(6, 1);    digitalWrite(7, 1);    digitalWrite(8, 1);    digitalWrite(9, 1);    digitalWrite(11, 1);  }
  if (number == 3) {    digitalWrite(5, 1);    digitalWrite(6, 1);    digitalWrite(8, 1);    digitalWrite(9, 1);    digitalWrite(11, 1);  }
  if (number == 4) {    digitalWrite(5, 1);    digitalWrite(8, 1);    digitalWrite(10, 1);    digitalWrite(11, 1);  }
  if (number == 5) {    digitalWrite(5, 1);    digitalWrite(6, 1);    digitalWrite(9, 1);    digitalWrite(10, 1);    digitalWrite(11, 1);  }
  if (number == 6) {    digitalWrite(5, 1);    digitalWrite(6, 1);    digitalWrite(7, 1);    digitalWrite(9, 1);    digitalWrite(10, 1);    digitalWrite(11, 1);  }
  if (number == 7) {    digitalWrite(5, 1);    digitalWrite(8, 1);    digitalWrite(9, 1);    digitalWrite(10, 1);  }
  if (number == 8) {    for (int j = 5; j <= 11; j++) {      digitalWrite(j, 1);    }  }
  if (number == 9) {    digitalWrite(5, 1);    digitalWrite(6, 1);    digitalWrite(8, 1);    digitalWrite(9, 1);    digitalWrite(10, 1);    digitalWrite(11, 1);  }}

void loop() {
  for (int i = 0; i <= 9; i++) { //i라는 변수를 0에서 시작하여 9보다 작거나 같다는 게 참인 경우 1씩 더하며 반복
    printnumber(i); //printnumber를 i에 해당하는 변수로 출력
    delay(1000);
  }
}