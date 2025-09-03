#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter; //BH1750의 이름을 lightMeter으로 설정

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();

}
void loop() {
  float lux = lightMeter.readLightLevel(); //lux라는 변수를 만들고 측정값을 저장
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}