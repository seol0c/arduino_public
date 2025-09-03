

//시프트레지스터(74HC595)를 이용한 8개의 LED 제어


//퍼온 자료임 제대로 검증하지 않음. 나중에 수정할 것


int datapin = 8;
int latchpin = 9;
int clockpin = 10;

byte digits[] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1B, 0x01, 0x09};

void setup()
{
  pinMode(latchpin, OUTPUT);
  pinMode(clockpin, OUTPUT);
  pinMode(datapin, OUTPUT);
}

void loop()
{
  for (int number = 0; number < 10; number++)
  {
    digitalWrite(latchpin, LOW);
    shiftOut(datapin, clockpin, LSBFIRST, digits[number]);
    digitalWrite(latchpin, HIGH);
    delay(500);
  }
}