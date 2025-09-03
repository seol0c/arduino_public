

//작성중




int SWITCH = 2;
int mode = 1;

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH, INPUT);
}

void loop() {
  int val = digitalRead(SWITCH);
  if (val == 1 && mode == 1) {
    delay(100);
    mode = 2;
    val = 0;
    delay(500);
  }
  if (val == 1 && mode == 2) {
    delay(100);
    mode = 3;
    val = 0;
    delay(500);
  }
  if (val == 1 && mode == 3) {
    delay(100);
    mode = 1;
    val = 0;
    delay(500);
  }
  Serial.print("스위치: ");
  Serial.print(val);
  Serial.print(", 모드: ");
  if (mode == 1) {
    Serial.println("초음파모드입니다.");
  }
  if (mode == 2) {
    Serial.println("라인트레이서모드입니다.");
  }
  if (mode == 3) {
    Serial.println("블루투스모드입니다.");
  }
}