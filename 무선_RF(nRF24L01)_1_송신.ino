/* nRF24L01모듈은 기본적으로 2.4GHz 대역을 사용하는 RF(Radio Frequency)통신 모듈이다.
  Bluetooth, ZigBee, NFC 모듈에 비해 가격이 매우 저렴하고 통신 가능 거리가 길지만
  RF통신의 특성상 장애물이 있을 경우 수신율이 떨어질 수 있다.
  일반적으로 트인 공간에서 100m 정도 송수신이 가능하며, 안테나를 이용하면 800m까지 가능하다.

  nRF24L01 모듈은 기본적으로 다대 다 통신이 가능하고
  1MHz 간격으로 125개의 주파수 채널을 운영할 수 있으며, 1대 다 통신도 가능하다.
  선택적 통신을 위해 5자리의 Address(주소)를 사용한다.

  모듈의 VCC 단자에는 1.9V~3.6V 입력만 가능하므로 아두이노에 연결 시 반드시 3.3V에 연결한다.
  - 어댑터가 있는 경우 레귤레이터가 있으므로 5V에 연결 가능
  - 호환아두이노 등은 (5V 주로 사용에 따른 비용 절감 등) 3.3V 레귤레이터 용량이 작아서
  어댑터를 이용하여 5V 주는 것이 더 좋기도 함

  소켓이 없는 경우 10uF 전해콘덴서를 이용하여 전원 보강을 해주면
  전원이 안정적으로 공급되어 송수신율을 높일 수 있다.
  노이즈 제거를 원하면 바이패스용으로 세라믹 콘덴서를 달아줄 수도 있다. */

/* 핀 연결은 안테나를 위로 가게 했을 경우 순서대로
  VCC - 3.3V
  CSN - 8
  MOSI - 11
  IRQ - 연결하지 않음
  GND - GND
  CE - 7
  SCK - 13
  MISO - 12
*/

// 라이브러리 필요함 RF-master.zip 추가

//아래는 송신코드, 테스트 안함

#include  <SPI.h>
#include  <nRF24L01.h>
#include  <RF24.h>
RF24 radio(7, 8); // SPI통신을 위한 (CE, CSN) 핀 선언
const byte address[6] = "00001"; // 송신기와 수신기를 동일한 값으로 주소 설정함(5자리)
void setup() {
  radio.begin();
  radio.openWritingPipe(address); // 데이터를 보낼 수신 주소를 설정
  radio.setPALevel(RF24_PA_MIN); // 송신거리에 따른, 전원공급 파워레벨 설정
  //(최소) RF24_PA_MIN → RF24_PA_LOW → RF24_PA_HIGH → RF24_PA_MAX (최대) 설정가능
  //송신이 약하다고 판단될 경우 nRF24모듈의 GND와 3.3V 단자에 전해콘덴서(10uF이상:+를3.3V연결)사용권장

  radio.stopListening();  // 모듈을 송신기로 설정
}
void loop() {
  const char text[] = "(From) nRF24 Tx : Hello World!"; // 송신할 문자
  radio.write(&text, sizeof(text));   // 위 문자를 문자 길이 만큼 송출함
  delay(1000);
}



