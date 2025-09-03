/*
  USB to TTL 을 사용하여 통신하는 경우 사용 전압, 보드에 맞게 연결해야 함

  YP-01 모델의 경우 PL2303 드라이버를 설치해야 함
  장치관리자의 포트에서 자동으로 설치된 PL2303HXA PHASED OUT SINCE 2012.... 을
  삭제(소프트웨어까지 완전 삭제)하고
  드라이버를 설치(폴더에 있음)하면 포트에서 Prolific USB-to-Serial Comm Port가 설치된 것을 확인할 수 있음

  참고로 "PL2303HXA PHASED OUT SINCE 2012. PLEASE CONTACT YOUR SUPPLIER" 란 오류가 발생한 경우
  Win10에서는 자동으로 최신 버전의 드라이브가 설치되는데
  해당 제품은 2012년도로 사용이 폐지된다는 내용으로 최신 드라이브와 해당 장치가 맞지 않는다는 내용임
  따라서 이전년도 드라이브를 다시 설치하면 문제가 해결된다.
*/

/*
  pro mini 업로드시
  툴 - 보드, 프로세서를 맞게 설정한 후(프로그래머는 바꿀 필요 없음)
  파일- 환경설정에서  "업로드 출력 자세히 보기"를 클릭한 뒤

  리셋 핀이 없는 경우(PL2303 등 4핀을 사용하는 TTL to USB 케이블)는
  자동리셋 기능이 없기 때문에 업로드 시 수동으로 리셋을 시켜줘야 함

  포트, 프로그래머, 보드레이트 등의 정보가 나올 때 즉시 리셋 버튼을 클릭해줘야 한다
  메세지 예시)
         System wide configuration file is "C:\Program Files (x86)\Arduino\hardware\tools\avr/etc/avrdude.conf"

         Using Port                    : COM9
         Using Programmer              : arduino
         Overriding Baud Rate          : 57600
*/

//FTDI USB시리얼 변환기를 사야 편할 듯...

#define led 13 //pro mini 내장 led는 13번 핀

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  delay(200);
}