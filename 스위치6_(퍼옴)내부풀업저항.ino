/* INPUT_PULLUP으로
   두개의 스위치를 연결해 LED 깜빡이는 속도를 조절하는 예제 */


#define SW1  8
#define SW2  9
#define LED  13

boolean gLedStat = HIGH;
int gSpd = 500;

void setup() {
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  static unsigned long last = 0;
  static unsigned long lastSw = 0;
  unsigned long now = millis();
  static boolean prev1 = HIGH;
  static boolean prev2 = HIGH;
  boolean cur;

  if ((now - lastSw) >= 10) {   // Check switch for every 10ms
    cur = digitalRead(SW1);
    if ((HIGH == prev1) && (LOW == cur)) {
      gSpd -= 100;
      gSpd = constrain(gSpd, 100, 2000);
      Serial.print("Delay up to ");
      Serial.println(gSpd);
      prev1 = LOW;
    } else if ((LOW == prev1) && (HIGH == cur)) {
      prev1 = HIGH;
    }
    cur = digitalRead(SW2);
    if ((HIGH == prev2) && (LOW == cur)) {
      gSpd += 100;
      gSpd = constrain(gSpd, 100, 2000);
      Serial.print("Delay down to ");
      Serial.println(gSpd);
      prev2 = LOW;
    } else if ((LOW == prev2) && (HIGH == cur)) {
      prev2 = HIGH;
    }
    lastSw = now;
  }
  if ((now - last) >= gSpd) {
    gLedStat = !gLedStat;
    digitalWrite(LED, gLedStat);
    last = now;
  }
}