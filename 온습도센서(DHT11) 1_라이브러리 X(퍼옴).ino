int DHT11 = 2;
int data[40];
int humidity;
int humidity2;
int temperature;
int temperature2;
int checksum;
int expect;

void setup() {
  Serial.begin(9600);
}

void loop() {
  readDHT11();
  Serial.print("humidity : ");
  Serial.print(humidity);
  Serial.print("    temperature : ");
  Serial.println(temperature);
  delay(1500);
}

void readDHT11() {
  humidity = -1;
  temperature = -1;
  pinMode (DHT11, OUTPUT);
  digitalWrite (DHT11, LOW);
  delay(20);
  digitalWrite (DHT11, HIGH);
  pinMode (DHT11, INPUT);
  delayMicroseconds (30);
  if (confirm (DHT11, 80, LOW)) {
    Serial.println("Error on Start LOW");
    return;
  }
  if (confirm (DHT11, 80, HIGH)) {
    Serial.println("Error on Start HIGH");
    return;
  }
  for (int i = 0; i < 40; i++) {
    if (confirm(DHT11, 50, LOW)) {
      Serial.println("Error on Data LOW");
      return;
    }
    bool ok = false;
    int tick = 0;
    for (int j = 0; j < 8; j++, tick++) {
      if (digitalRead(DHT11) != HIGH) {
        ok = true;
        break;
      }
      delayMicroseconds(10);
    }
    if (!ok) { //
      Serial.println("Error on Data Read");
      return;
    }
    data[i] = (tick > 3 ? 1 : 0);
  }
  if (confirm(DHT11, 50, LOW)) {
    Serial.println("Error on End of Reading");
    return;
  }
  humidity = bits2byte(data);
  humidity2 = bits2byte(data + 8);
  temperature = bits2byte(data + 16);
  temperature2 = bits2byte(data + 24);
  checksum = bits2byte(data + 32);

  expect = humidity + humidity2 + temperature + temperature2;
  if (checksum != expect) {
    Serial.println("there are some error on Transmission");
    humidity = -1;
    temperature = -1;
  }
}

int confirm (int pin, int us, byte level) {
  int count = us / 10;
  if ((us % 10) > 0) count++;

  bool ok = false;
  for (int i = 0; i < count; i++) {
    delayMicroseconds(10);

    if (digitalRead(pin) != level) {
      ok = true;
      break;
    }
  }
  if (!ok) {
    return -1;
  }
  return 0;
}

int bits2byte(int data[8]) {
  int v = 0;
  for (int i = 0; i < 8; i++) {
    v += data[i] << (7 - i);
  }
  return v;
}