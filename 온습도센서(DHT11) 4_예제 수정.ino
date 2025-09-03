#include <SimpleDHT.h>
int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  Serial.begin(9600); //여러 모듈을 사용할 수 있으므로 많이 쓰이는 9600 사용
}

void loop() {
  Serial.println("================================="); //실선 출력
  byte temperature = 0;
  byte humidity = 0;

  //에러가 났을 경우 메세지 출력 등에 관한 코드를 제거하였음(에러가 나면 그냥 출력을 안하면 됨)

  dht11.read(&temperature, &humidity, NULL); //핵심이 되는 코드: DHT11의 값을 읽음

  Serial.print("온도 : "); //온도를 알리는 문구를 출력
  Serial.print((int)temperature); Serial.print(" ºC, ");
  Serial.print("습도 : "); //습도를 알리는 문구를 출력
  Serial.print((int)humidity); Serial.println(" %RH"); //상대습도 출력 후 줄바꿈
  //시리얼모니터는 영어뿐만 아니라 한글, 특수문자 출력이 가능

  delay(1500);
}

/* DHT11은 상대습도(Relative Humidity)를 사용하며, 상대습도의 단위는 %RH입니다.
  대기 중에 포함된 실제 수증기량과 해당 온도에서 포함할 수 있는 최대 수증기량의 비를
  백분율로 표시한 것입니다.
  DHT11의 값을 읽는데에는 약 1초의 시간이 걸리므로 1초 이상의 지연시간을 줍니다. */