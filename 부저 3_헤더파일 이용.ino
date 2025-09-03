/*
  헤더파일에 미리 노트를 선언해두고 불러다가 쓸 수 있습니다.(엔트리에서 함수 사용과 비슷)
  시리얼모니터 아이콘 아래에 화살표를 눌러 탭을 추가하고 pitches.h로 이름을 지정하여 사용합니다.
  파일을 저장하면 같은 폴더에 ino 파일과 h파일이 함께 저장되며 헤더파일을 사용할 수 있습니다.

  "예제 - Digital - toneMelody"을 실행하면 헤더파일이 포함되어 있습니다.
  아래는 예제 파일이며 헤더파일을 이용한 멜로디연주를 분석해보겠습니다.
*/


#include "pitches.h" //pitches.h(헤더파일)

int melody[] = { //melody 선언, 집합으로 표시하여 순서대로 원소들을 나열하였습니다. 8개의 음계를 순서대로 사용할 예정입니다.
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = { //음계지속시간"들"을 선언하고 집합으로 표시하였습니다. 4분음표, 8분음표로 사용할 것입니다.
  //[1]은 첫 번째 원소를 의미하며, 값은 4입니다. [2], [3]은 8입니다.
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() { //1회만 시행하고 반복하지 않을 것입니다.
  for (int thisNote = 0; thisNote < 8; thisNote++) { //thisNote를 선언하여 0부터 시작하여 8보다 작다면 1씩 더합니다.(반복의 개념)

    //음계지속시간 계산을 위하여 1초를 노트타입으로 나누어줍니다.
    //예를 들면, 4분음표는 1000/4, 8분음표는 1000/8으로 설정합니다.

    int noteDuration = 1000 / noteDurations[thisNote]; //위의 계산식을 이용하여 음계지속시간을 다시 선언합니다.
    //int[int]오류를 막기 위하여 처음 noteDurations으로 선언한 것입니다.
    tone(8, melody[thisNote], noteDuration); //8번핀(부저이름으로 선언하지 않음)에 대한 톤함수

    //음계간 구분을 위하여 딜레이를 해줍니다. 이때 음의 지속시간에 30%정도가 적당합니다.
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8); //출력을 중단합니다.
  }
}

void loop() { //멜로디를 반복(loop)하지 않고 코드를 종료합니다. 반복하지 않더라도 필수함수로 꼭 적어줘야합니다.
}