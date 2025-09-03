
/*

  2023.01.07. nodeMCU 보드 설치

  1. open up Arduino IDE. Go to Files-> Preferences. Enter
  http://arduino.esp8266.com/stable/package_esp8266com_index.json
  into Additional Board Manager URLs field

  2. Now go to Tools->Boards->Board Manager
  and search for ESP8266 and install the package.

  3. 툴-보드에서 그냥 generic esp8266 선택함

*/

#define led 16

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH); //nodeMCU의 경우 high에서 led가 꺼짐
  delay(500);
  digitalWrite(led, LOW);
  delay(2000);
}

/* nodeMCU의 경우 16번이 내장 led인데
  PIO16이 led의 -극에 연결이 되어있음
  즉 low 상태에서 led가 3.3V를 입력받아 불이 켜지게 됨
  위의 코드는 low가 2초이므로 오랜 시간 켜지고 잠깐 꺼지는 코드임
*/