#include <Wire.h> //for I2C
#include <BH1750.h>
#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>

int pinDHT11 = 3;
int Window = 0;

SimpleDHT11 dht11(pinDHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);
BH1750 lightMeter;

byte customChar0[] = {  //fire
  B00000,  B00010,  B10110,  B01101,
  B01110,  B11111,  B11111,  B01110
};

byte customChar1[] = {  //water
  B00000,  B00100,  B00110,  B01111,
  B11111,  B11111,  B11111,  B01110
};

byte customChar2[] = {  //sun
  B00100,  B10101,  B01110,  B11011,
  B01110,  B10101,  B00100,  B00000
};

byte customChar3[] = {  //moon
  B00100,  B01110,  B11001,  B10000,
  B10000,  B11001,  B01111,  B00110
};

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customChar0);
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  lcd.createChar(3, customChar3);
  Wire.begin();
  lightMeter.begin();
}

void loop() {
  lcd.clear();
  byte temperature = 0;
  byte humidity = 0;
  float lux = lightMeter.readLightLevel();
  dht11.read(&temperature, &humidity, NULL);
  int H = (int)humidity;
  int T = (int)temperature;
  int L = (int)lux;
  lcd.setCursor(0, 0);
  lcd.write(0); lcd.print(T); lcd.print(" ");
  lcd.write(1); lcd.print(H); lcd.print(" ");
  if (L > 300) {
    lcd.write(2);
  }
  else {
    lcd.write(3);
  }
  lcd.print(L);
  if (H > 90 && Window == 0) {
    for (int i = 0; i < 2; i++) {
      lcd.setCursor(0, 1);
      lcd.print(" Window Opened!");
      delay(500);
      lcd.setCursor(0, 1);
      lcd.print("                ");
      delay(500);
    }
    Window = 1;
  }
  if (H < 90 && Window == 1) {
    for (int i = 0; i < 2; i++) {
      lcd.setCursor(0, 1);
      lcd.print(" Window Closed!");
      delay(500);
      lcd.setCursor(0, 1);
      lcd.print("                ");
      delay(500);
    }
    Window = 0;
  }
  delay(1100);
}