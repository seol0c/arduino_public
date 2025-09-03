
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define Button 7
int potentiometer = A0;
int buzz = 8;
int overf = 0;

volatile int flow_frequency; //유량센서 측정 pulse의 진동수
float l_sec; // Calculated litres/hour
int flowsensor = 2; // 센서값
unsigned long currentTime;
unsigned long cloopTime;
void flow () // Interrupt function
{
  flow_frequency++;
}
void setup()
{
  lcd.init();
  lcd.backlight();
  pinMode(Button, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
  attachInterrupt(0, flow, RISING); // Setup Interrupt
  sei(); // Enable interrupts
  currentTime = millis();
  cloopTime = currentTime;
}
void loop ()
{
  currentTime = millis();
  // Every second, calculate and print litres/hour
  if (currentTime >= (cloopTime + 1000)) {
    cloopTime = currentTime; // Updates cloopTime
    // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
    l_sec = (flow_frequency / 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
    int AI = analogRead(potentiometer);
    AI = map(AI, 0, 1023, 0, 100);
    float AI_2 = AI / 10.0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("set: ");
    lcd.print(AI_2, 1);
    lcd.print("L  ");
    if (overf == 1) {
      lcd.print("Bell");
    }
    lcd.setCursor(0, 1);
    lcd.print("tot: ");
    lcd.print(l_sec, 1);
    lcd.print("L");
    if ( l_sec >= AI_2 && overf == 0) {
      overf = 1;
      tone(buzz, 800);
      delay(2000);
      noTone(buzz);
      delay(100);
    }
    int ButtonValue = digitalRead(Button);
    if (ButtonValue == 1) {
      flow_frequency = 0;
      overf = 0;
    }
  }
}