
/*
  원래 모터 연결에 3,5,6,9 핀을 사용함
  모든 부분에서 잘 작동하였으나
  리모컨(2번 핀 연결)을 이용한 제어 시 3번 핀의 아날로그 출력이 되지 않는 현상을 발견
  그래서 그냥 5,6,9,10핀을 사용하여 모터를 연결하게 됨(리모컨 동작 잘 됨)
*/

#define a1 5 //모터드라이버의 a와 b(각각 핀 2개)를 변수 설정
#define a2 6
#define b1 9
#define b2 10

/* 모터의 선과 모터드라이버 연결이 a,b +,-가 반대로 연결된 경우
  또는 연결상태는 같아보여도 모터가 뒤집어져있는 경우
  같은 코드더라도 오른쪽 바퀴, 왼쪽 바퀴, 전진, 후진이 다를 수 있습니다.
  아래의 숫자를 0~255로 바꿔보며 바퀴가 어떻게 움직이는지 먼저 체크하세요. */

void setup() {
  pinMode(a1, OUTPUT); //모터드라이버의 각 핀을 출력모드로 설정
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);

  //3초간 a1,a2,b1,b2의 값을 하나씩변화시키며 왼쪽, 오른쪽, 정방향, 역방향을 체크합니다.
  analogWrite(a1, 200);
  analogWrite(a2, 0);
  analogWrite(b1, 0);
  analogWrite(b2, 0);
  delay(3000);

  analogWrite(a1, 0); //모든 출력 정지
  analogWrite(a2, 0);
  analogWrite(b1, 0);
  analogWrite(b2, 0);
}

void loop() { //테스트를 위하여 반복하지 않고 setup을 이용하여 1회만 실행합니다.
}