#include <Servo.h>
/* L9110s 모터드라이버
   오른쪽모터
   L9110s A_1A D6
   L9110s A_1B D11
   왼쪽모터
   L9110s B_1A D3
   L9110s B_1B D5
*/
int A_1A = 6;
int A_1B = 11;
int B_1A = 3;
int B_1B = 5;
/*
   초음파센서
   초음파센서 TRIG - D8
   초음파센서 ECHO - D9
*/
int trigPin = 8;
int echoPin = 9;
/*
   서보모터
   서보모터 OUT - D10
*/
int servoPin = 10;

Servo servo;

//모터의 좌우 속도가 다를 경우,
//아래의 변수를 조정하여 해결할 수 있습니다.

int motorASpeed = 150; // 모터A 속도 (0~255)
int motorBSpeed = 150; // 모터B 속도 (0~255)

void setup() {
  // 문제발생시 테스트를 위해 시리얼모니터를 시작합니다.
  Serial.begin(9600);
  //핀을 초기화합니다.
  //L9110S 모터드라이버의 핀들을 출력으로 변경합니다.
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);

  //초음파센서를 초기화합니다. Trig
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //서보모터를 연결합니다.
  servo.attach(servoPin);

  //초기에 서보를 정면을 봅니다
  servo.write(90);
  delay(1000);
}

void loop() {
  int cm = getStableDistanceCM();
  long leftDistance = 0;
  long rightDistance = 0;

  //25cm이내에 벽이 있다면 아래의 코드를 실행합니다.
  if (cm < 25) {
    //0.5초간 정지합니다.
    stop();
    delay(500);
    //왼쪽 거리를 변수에 저장합니다.
    servo.write(150);
    delay(500);
    leftDistance = getStableDistanceCM();
    delay(500);
    //오른쪽 거리를 변수에 저장합니다.
    servo.write(30);
    delay(500);
    rightDistance = getStableDistanceCM();
    delay(500);
    //      서보모터를 중앙으로 움직입니다.
    servo.write(90);
    delay(1000);
    //       0.3초간 후진합니다.
    back();
    delay(300);
    /*
      왼쪽이 오른쪽보다 크다면 0.5초간 좌회전하며,
      아니라면(작다면)  0.5초간 우회전합니다.
    */
    if (leftDistance > rightDistance) left();
    else right();

    delay(500);
    //   25cm이내에 벽이 없다면 전진합니다.
  }
  else {
    forward();
  }
}

/**
   전방 거리측정(CM)
   초음파센서를 이용해서 벽까지의 거리(mm)를 구합니다.
*/
float getDistanceCM() {
  digitalWrite(echoPin, LOW);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //    거리값을 저장합니다.
  float distance = pulseIn(echoPin, HIGH)  / 29.0 / 2.0;

  return distance;
}
/**
   전방 신뢰할 수 있는 거리측정(CM)
   초음파센서를 여러번 나누어 신뢰할 수 있는 거리값을 구합니다.
   주의: 초음파센서 등 많은 측정 센서들의 경우, 중간에 값의 오차가 발생하는 경우로 인해 오동작을 유발하므로, 여러번 측정 후 평균값을 구하는 방식으로 개선하여 사용합니다.
   만약 다음과 같이 해도 허공에서 물체를 감지하는 등의 문제가 발생한다면 10이 아닌 다른 수로 변경하시어 테스트하셔도 됩니다.
*/
float getStableDistanceCM() {
  int CmSum = 0;

  for (int i = 0; i < 10; i++) {
    CmSum += getDistanceCM();
  }

  return CmSum / 10;
}

/**
   RC카 전진
   왼쪽,오른쪽 모터를 정회전하여 전진합니다.
*/
void forward() {
  //모터A 정회전
  analogWrite(A_1A, motorASpeed);
  analogWrite(A_1B, 0);
  //모터B 정회전
  analogWrite(B_1A, motorBSpeed);
  analogWrite(B_1B, 0);
}

/**
   RC카 후진
   왼쪽,오른쪽 모터를 역회전하여 후진합니다.
*/

void back() {
  //모터A 역회전
  analogWrite(A_1A, 0);
  analogWrite(A_1B, motorASpeed);
  //모터B 역회전
  analogWrite(B_1A, 0);
  analogWrite(B_1B, motorBSpeed);
}

/**
   RC카 좌회전
   오른쪽 모터를 정회전, 왼쪽모터를 정지하여 좌회전합니다.
*/
void left() {
  //모터A 역회전
  analogWrite(A_1A, motorASpeed);
  analogWrite(A_1B, 0);
  //모터B 정회전
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);
}

/**
   RC카 우회전
   오른쪽 모터를 정지, 왼쪽 모터를 정회전하여 우회전합니다.
*/

void right() {
  //모터A 정회전
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  //모터B 역회전
  analogWrite(B_1A, motorBSpeed);
  analogWrite(B_1B, 0);
}

/**
   RC카 정지
   오른쪽,왼쪽모터를 모두 정지합니다.
*/
void stop() {
  //모터A 정지
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  //모터B 정지
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);
}