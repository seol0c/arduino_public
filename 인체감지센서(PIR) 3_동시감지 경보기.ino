//초음파센서, 인체감지센서 동시 적용 경보기

int PIR = 7; //인체감지센서 7번핀
int act = 12; //led 또는 능동부저, 모터 등
int PIRstate = LOW; //PIR상태를 초기에 LOW로
int val = 0; //PIR을 저장할 초기값을 0으로 선언

#define trig 8    //트리거 핀 8
#define echo 9    //에코 핀 9

void setup() {
  pinMode(PIR, INPUT);
  pinMode(act, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(PIR);   //PIR값 저장
  long duration, distance;  //초음파 센서 공식
  //거리 측정을 위한 변수 선언, 트리거 핀으로 10us 동안 펄스 출력
  digitalWrite(trig, LOW);
  delayMicroseconds(2);             //딜레이 2us
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);            //딜레이 10us
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 170 / 1000; //초음파 공식 끝
  Serial.print("모션: X / 거리:");
  Serial.print(distance); //거리를 시리얼 모니터에 출력
  Serial.println("mm");
  delay(100);
  if (distance < 3000) {
    digitalWrite(act, HIGH);
    Serial.print("모션: X / 거리:");
    Serial.print(distance); //거리를 시리얼 모니터에 출력
    Serial.println("mm");
  }
  else {
    if (val == HIGH) { //PIR 감지시
      digitalWrite(act, HIGH); //act를 HIGH
      if (PIRstate == LOW) {  //PIR 상태가 LOW라면
        Serial.println("******");
        Serial.print("모션: O / 거리:");
        Serial.print(distance); // 거리를 시리얼 모니터에 출력
        Serial.println("mm");
        Serial.println("******");
        PIRstate = HIGH;      //시리얼 모니터 출력 후 HIGH로 변경
      }
    }
    else {  //그렇지 않을 시 act는 LOW로, PIR 상태가 HIGH였다면 모션 끝 알리고 LOW로 바꾸기
      digitalWrite(act, LOW);
      if (PIRstate == HIGH) {
        Serial.print("모션: X / 거리:");
        Serial.print(distance); //거리를 시리얼 모니터에 출력
        Serial.println("mm");
        PIRstate = LOW;
      }
    }
  }
}