
//초음파 센서는 공식화 된 것을 그대로 이용하면 됨
//라이브러리를 사용할 수도 있지만 직접 코드를 작성해봅시다.

#define trig 8 //트리거 핀 8
#define echo 9 //에코 핀 9, 에코와 트리거는 모든 디지털 핀에 연결 가능

void setup() {
  pinMode(trig, OUTPUT); //trig를 출력으로 설정
  pinMode(echo, INPUT); //echo를 입력으로 설정
  Serial.begin(9600); //시리얼 통신을 시작. 통신 속도는 9600
}

void loop() {
  //트리거 핀으로 10us(10마이크로초, 백만분의 10초) 동안 펄스 출력
  digitalWrite(trig, LOW); //처음 꺼진 상태로 설정
  delayMicroseconds(2); //딜레이 2us
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); //딜레이 10us
  digitalWrite(trig, LOW);

  /* 에코에서 받은 펄스 값을 pulseIn함수를 호출하여
    펄스가 입력될 때까지의 시간을 us단위로 duration에 저장
    pulseln() 함수는 핀에서 펄스(HIGH or LOW)를 읽어서 마이크로초 단위로 반환 */

  long duration, distance; //거리 측정을 위한 변수 선언
  duration = pulseIn(echo, HIGH);

  /* 음파의 속도는 초당 340m, 왕복하였으니 나누기 2를하면 170m이고,
    mm단위로 바꾸면 170,000mm.
    duration에 저장된 값은 us단위이므로 1,000,000으로 나누어 주고,
    정리해서 distance에 저장
    즉, 시간과 소리의 속도를 이용하여 거리를 mm로 구하는 공식 */

  distance = duration * 170 / 1000; //10,000으로 나누면 cm로 구할 수 있음

  Serial.print("거리: ");
  Serial.print(distance); //거리를 시리얼 모니터에 출력
  Serial.println("mm");
  delay(100);
}