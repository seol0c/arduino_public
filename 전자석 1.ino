int electromagnet = 2;

void setup() {
  pinMode(electromagnet, OUTPUT);
}

void loop() {
  digitalWrite(electromagnet, HIGH);
  delay(1000);
  digitalWrite(electromagnet, LOW);
  delay(1000);
}