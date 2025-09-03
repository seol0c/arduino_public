
/* 테스트가 끝났으면 전진, 후진의 함수를 만들어봅시다.
  아날로그 출력을 위하여 속도값을 변수로 설정해봅시다. */

#define a1 5 //모터드라이버의 a와 b(각각 핀 2개)를 변수 설정
#define a2 6
#define b1 9
#define b2 10
#define HighSpeed 255 //빠른 속도의 출력을 255(최대값)으로 설정
#define LowSpeed 180 //느린 속도의 출력을 180으로 설정

void setup() {
  pinMode(a1, OUTPUT); //모터드라이버의 각 핀을 출력모드로 설정
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
}

void loop() {
  forward(); //forward라는 함수 실행. 함수의 내용은 아래에 작성
  delay(1000);
  back();
  delay(1000);
}

//함수 생성시 위치는 보통 아래에 작성함
//void형 함수끼리 병렬로 구성되므로 생성된 함수는 위에 있을 필요 없음

void forward() {
  analogWrite(a1, HighSpeed);
  analogWrite(a2, 0);
  analogWrite(b1, HighSpeed);
  analogWrite(b2, 0);
}

void back() {
  analogWrite(a1, 0);
  analogWrite(a2, HighSpeed);
  analogWrite(b1, 0);
  analogWrite(b2, HighSpeed);
}

/* 위와 같은 함수를 만들어 낸 경우
  코드 상에서 forward(); 만 입력하면 미리 지정된 함수가 실행됩니다.

  void 함수(변수) {
    함수의 내용
  }

  의 형태로 실행하며 속도 값을 변수로 지정하는 경우

  void forward(int Speed) {
    analogWrite(a1, Speed);
    analogWrite(a2, 0);
    analogWrite(b1, Speed);
    analogWrite(b2, 0);
  }

  로 작성할 수 있습니다. 위와 같은 형태는 변수가 반드시 필요하므로

  forward(200); //전진 속도 200
  forward(300); //전진 속도 300

  와 같은 형태로 함수를 실행해야 합니다.
  
  속도가 아닌 지연시간을 변수로 지정할 수도 있습니다.
  자동화 운전의 경우
  
  forward(1000); //1초간 전진
  left(500); //0.5초간 좌회전
  
  등으로 코드를 구성할 수 있습니다. */