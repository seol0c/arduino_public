#include <OLED_I2C.h>

OLED oled(SDA, SCL, 8);

extern uint8_t SmallFont[]; //글꼴 배열 외부에서 가져옴

void setup()
{
  oled.begin();
  oled.setFont(SmallFont); //글꼴 설정
}

void loop()
{
  oled.clrScr(); //디스플레이 지움
  oled.print("hi", 0, 0); //0,0에 hi 출력 (첫 번째 줄)
  oled.print("bye", 0, 11); //0,10에 bye 출력 (두 번째 줄)
  oled.print("bb", 0, 55); //마지막 줄
  oled.update(); //디스플레이 업데이트(반영)
}
