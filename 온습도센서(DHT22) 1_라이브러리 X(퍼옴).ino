
//라이브러리 없이 작성된 코드

byte value();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte data[5] = {0}, tmp = 0;
  int T = 0, H = 0;

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(2, LOW);
  delay(1); //Tbe
  digitalWrite(2, HIGH);
  delayMicroseconds(30); //Tgo
  pinMode(2, INPUT);
  if (digitalRead(2) == HIGH) {
    Serial.println("Tbe or Tgo error");
    return;
  }
  delayMicroseconds(80); //Trel
  if (digitalRead(2) == LOW) {
    Serial.println("Trel error");
    return;
  }
  delayMicroseconds(80); //Treh
  if (digitalRead(2) == HIGH) {
    Serial.println("Treh error");
    return;
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 8; j++) {
      if (j < 7) {
        data[i] |= value();
        data[i] = data[i] << 1;
      }
      else
        data[i] |= value();
    }
  }

  delayMicroseconds(50); //Ten
  if (digitalRead(2) == LOW) {
    Serial.println("Ten error");
    return;
  }

  for (int i = 0 ; i < 4; i++) tmp += data[i];

  if (data[4] == tmp) {
    H = data[0] << 8;
    H |= data[1];
    T = data[2] << 8;
    T |= data[3];
    Serial.print("Temp : ");
    if (data[2] >> 7 == 1) {
      Serial.print("-");
      T = T - 32768;
    }
    Serial.print(T / 10);
    Serial.print(".");
    Serial.print(T % 10);
    Serial.print("C  Humidity : ");
    Serial.print(H / 10);
    Serial.print(".");
    Serial.print(H % 10);
    Serial.println("%");
  }
  else
    Serial.println("Parity error");

  delay(2000);
}

byte value() {
  byte va = 0;

  while (digitalRead(2) == LOW) delayMicroseconds(1); //Tlow
  delayMicroseconds(50);
  if (digitalRead(2) == LOW) va |= 0;
  else {
    va |= 1;
    while (digitalRead(2) == HIGH) delayMicroseconds(1);
  }

  return va;
}