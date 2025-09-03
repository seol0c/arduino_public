//필요 라이브러리: Rtc by Makuna
//DS1302 검색하면 됨

/* 본 코드는 DS1302_Simple 예제의 핵심 코드만 추려서 새로 작성한 것입니다.
  DS1302_Memory를 통해 시간을 입력하고 본 코드를 실행할 수 있습니다. */

/*핀 연결
  VCC - 5V
  GND - GND
  CLK - D5
  DAT - D4
  RST - D2
*/

/* 시간이 고정되어 움직이지 않는다면 건전지와 IC칩(DS1302)을 뺐다가 다시 꽂아 리셋시키세요. */

#include <ThreeWire.h>
#include <RtcDS1302.h>
ThreeWire myWire(4, 5, 2); //핀 설정
RtcDS1302<ThreeWire> Rtc(myWire); //RTC의 이름과 핀 설정

void setup() {
  Serial.begin(9600); //시리얼 통신 시작
  Rtc.Begin(); //RTC 통신 시작
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime(); //RTC 시간값을 읽어서 now라는 변수에 저장
  if (now.Hour() < 10) {
    Serial.print("0");
  }
  Serial.print(now.Hour()); //"시간"을 정수 형태로 표시(10보다 작으면 앞에 0 추가)

  Serial.print(":");
  if (now.Minute() < 10) {
    Serial.print("0");
  }
  Serial.print(now.Minute()); //"분"을 정수 형태로 표시(10보다 작으면 앞에 0 추가)

  Serial.print(":");
  if (now.Second() < 10) {
    Serial.print("0");
  }
  Serial.println(now.Second()); //"초"를 정수 형태로 표시(10보다 작으면 앞에 0 추가)하고 줄바꿈
  delay(1000);
}