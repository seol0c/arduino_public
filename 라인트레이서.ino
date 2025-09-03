int LineSensor =  7;


void setup() {
  Serial.begin(9600);
  pinMode(LineSensor, INPUT); //라인센서를 입력모드로 설정
}

void loop() {
  int val = digitalRead(LineSensor);
  Serial.println(val);
}