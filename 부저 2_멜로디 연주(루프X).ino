/*
  "떳다 떳다 비행기" 멜로디 연주를 해봅시다.
  2093(도),2349(레),2637(미),2793(파),3136(솔),3520(라),3951(시),4186(도)
*/

int buzzer = 8; //8번핀을 "buzzer"로 선언

void setup() { //1회만 시행하고 반복하지 않을 것입니다.
  tone(buzzer, 2637); //미
  delay(500);
  tone(buzzer, 2349); //레
  delay(500);
  tone(buzzer, 2093); //도
  delay(500);
  tone(buzzer, 2349); //레
  delay(500);
  tone(buzzer, 2637); //미
  delay(500);
  tone(buzzer, 2637); //미
  delay(500);
  tone(buzzer, 2637); //미
  delay(500);
  tone(buzzer, 2349); //레
  delay(500);
  tone(buzzer, 2349); //레
  delay(500);
  tone(buzzer, 2349); //레
  delay(500);
  tone(buzzer, 2637); //미
  delay(500);
  tone(buzzer, 3136); //솔
  delay(500);
  tone(buzzer, 3136); //솔
  delay(800);
  tone(buzzer, 2637); //미
  delay(500);
  tone(buzzer, 2349); //레
  delay(500);
  tone(buzzer, 2093); //도
  delay(500);
  tone(buzzer, 2349); //레
  delay(500);
  tone(buzzer, 2637); //미
  delay(500);
  tone(buzzer, 2637); //미
  delay(500);
  tone(buzzer, 2637); //미
  delay(500);
  tone(buzzer, 2349); //레
  delay(500);
  tone(buzzer, 2349); //레
  delay(500);
  tone(buzzer, 2637); //미
  delay(500);
  tone(buzzer, 2349); //레
  delay(500);
  tone(buzzer, 2093); //도
  delay(500);
  noTone(buzzer);
}

void loop() { //멜로디를 반복(loop)하지 않고 코드를 종료합니다. 반복하지 않더라도 필수함수로 꼭 적어줘야합니다.

}