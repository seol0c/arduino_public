#include <SPI.h> //RFID를 위한 SPI 라이브러리
#include <MFRC522.h> //RFID 라이브러리

#define SS_PIN 10 //RFID SS(SDA:ChipSelect)핀
#define RST_PIN 9 //RFID Reset핀
MFRC522 rfid(SS_PIN, RST_PIN); //RFID 이름을 rfid로 지정

int LED = 7; //LED 연결

/* 등록된 RF CARD ID를 순서대로 작성합니다.
  예를 들어 In hex:  84 68 9A EA
  위와 같다면 아래와 같이 기입합니다. */

#define PICC_0 0x84
#define PICC_1 0x68
#define PICC_2 0x9A
#define PICC_3 0xEA

void setup() {
  Serial.begin(9600);
  SPI.begin(); //SPI 시작
  rfid.PCD_Init(); //RFID 모듈 시작
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent()) //카드가 인식 안될 경우 더이상 진행하지 않고 빠져나감
    return;
  if ( ! rfid.PICC_ReadCardSerial()) //RF카드의 ID가 인식 안될 경우 더이상 진행하지 않고 빠져나감
    return;

  Serial.print(F("PICC type: ")); //PICC 타입 읽어오기
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) { //MIFARE 방식이 아닌 경우 더이상 진행하지 않고 빠져나감
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if ((rfid.uid.uidByte[0] == PICC_0) &&
      (rfid.uid.uidByte[1] == PICC_1) &&
      (rfid.uid.uidByte[2] == PICC_2) &&
      (rfid.uid.uidByte[3] == PICC_3) ) { //등록된 ID와 일치하는 경우

    Serial.println("등록된 카드입니다.");
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);

  } else {
    Serial.println("등록되지 않은 카드입니다.");
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size); //등록된 ID와 일치하지 않는 경우 ID 표시
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1(); //모듈 종료
}

void printHex(byte *buffer, byte bufferSize) { //16진수(HEX) 표시를 위한 코드
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}