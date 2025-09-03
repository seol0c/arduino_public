






//퍼왔음 수정해야 함




#include <Servo.h>  // 서보 라이브러리
#include <SPI.h>    // RFID를 위한 SPI 라이브러리
#include <MFRC522.h>// RFID 라이브러리

#define SERVO_PIN 6 //서보 PIN
Servo myservo;      //서보 라이브러리

#define SS_PIN 10   //RFID SS(SDA:ChipSelect) PIN
#define RST_PIN 9   //RFID Reset PIN
MFRC522 rfid(SS_PIN, RST_PIN); //RFID 라이브러리


/* 등록된 RF CARD ID */
#define PICC_0 0x16 
#define PICC_1 0x35
#define PICC_2 0x8A
#define PICC_3 0xAB


void setup() { 
  //시리얼 모니터 시작
  Serial.begin(9600);
  SPI.begin(); // SPI 시작
  rfid.PCD_Init(); // RF 모듈 시작

  myservo.attach(SERVO_PIN); //서보 시작
  myservo.write(0); //초기 서보 모터를 0도로 위치 시킴
}
 
void loop() {
  //카드가 인식 안되었다면 더이상 진행하지 말고 빠져나감
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  //RF카드의 ID가 인식 안되었다면 더이상 진행하지 말고 빠져나감
  if ( ! rfid.PICC_ReadCardSerial())
    return;


  Serial.print(F("PICC type: "));
  //PICC 타입 읽어오기
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));


  //MIFARE 방식이 아니라면 더이상 진행하지 말고 빠져나감
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }


  //ID가 등록된 ID와 동일하다면
  if (rfid.uid.uidByte[0] != PICC_0 || 
      rfid.uid.uidByte[1] != PICC_1 || 
      rfid.uid.uidByte[2] != PICC_2 || 
      rfid.uid.uidByte[3] != PICC_3 ) {

   
    Serial.println(F("This is a confirmed Card."));   
    Serial.println(F("Motor On!!"));   

    //서보 90도로 이동
    myservo.write(90);
    //1초 대기
    delay(1000);
    //서보 0도로 되돌림
    myservo.write(0);
  }else{
    //등록된 카드가 아니라면 시리얼 모니터로 ID 표시
    Serial.println(F("This is an unconfirmed Card."));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);    
  }
  
  //종료
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  //다시 시작!
}

//16진수 표시
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}