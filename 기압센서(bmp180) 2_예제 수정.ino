#include <Arduino.h>
#include <Wire.h>
#include <BMP180I2C.h>

BMP180I2C bmp180(0x77);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  bmp180.begin();
  bmp180.resetToDefaults();
  bmp180.setSamplingMode(BMP180MI::MODE_UHR); //높은 해상도의 압력 측정 모드 사용(선택)
}

void loop() {
  Serial.print("Temperature: ");
  Serial.print(bmp180.readTemperature());
  //값을 읽고 그것을 get하는 방식에서 read로 변경
  //do, while을 통해 측정값을 얻고 bmp.get~을 이용하여 값을 얻는 과정이 길고 복잡하므로 read로 변경
  Serial.println(" degC");
  Serial.print("Pressure: ");
  Serial.print(bmp180.readPressure());
  Serial.println(" Pa");
  delay(1000);
}