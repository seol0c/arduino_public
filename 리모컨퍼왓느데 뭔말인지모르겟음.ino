/*
기존 코딩을 할때 보면 리모콘 버튼을 꾹 누르면 FFFFFFFF값만 지속적으로 나오고 실제로는 연속동작은 되지 않았다.
예를 들어 볼륨을 올릴려 하는데, 원래라면 꾹 누르면 볼륨이 쭈루룩 올라가야 하는데,
꾹 눌러도 볼륨이 쭈루룩 올라가지 않고 한 번만 올라간다는 뜻이다.
구글링 해도 뭔지는 몰라서 봤는데, 구글에서도 사실상 찾기 힘들었다.
대부분 FFFFFFFF값 나오면 성공한거라고 보였기 때문이다.
맞는 말이지만 효과는 없는 것이다.

그런데, 이 문제를 해결하는건 의외로 간단했다.
loop 영역에서 if문을 추가하는 것이였다.
if(리모콘 수신값==0xFFFFFFFF){리모콘(이전에 저장한 값);}
이 문장을 추가한 다음에, 
리모콘 함수에 있는 switch - case 문 안에 있는 값 중에서 
쭈루루룩 누르고 싶은 특정 버튼이 있을 것이다.
break; 이전에 "이전에 저장한 값=리모콘 수신값;" 이라는 문장을 추가 하면 된다.
그러면 if문 밖에 있는 스위치 값으로 시작해서 if문 안에 있는 스위치 값이 순환하게 되어 
볼륨을 쭈루룩 올릴 수 있다는 거였다.

아래는 내가 실습할때 만든 코드중 일부다.
라인트레이서와, 초음파센서, 리모콘, 서보모터 등이 들어간 형태다.

내가 빨간색으로 표시한 영역이 이 글의 핵심이다.
파란색은 이 글에서 보조되는 요소다.

te=val; 이 부분은 내가 쭈루룩 입력되는걸 원하는 버튼을 설정한 경우고
te=0; 은 버튼을 꾹 눌러도 한 번만 입력하길 원하는 버튼을 설정한 경우다.

그런데 맨 아래에 te=0을 빨간색으로 표시한 이유는,
리모콘 잡음에 의한 버튼 오작동을 막기위한 것이다.

리모콘 잡음으로 인해서 무작위 값이 반복되어 FFFFFFFF 가 입력되는 경우가 있다.
물론 파란색으로 표시한 영역도 저렇게 해야 꾹 눌러서 FFFFFFFF가 나와서 다른 키가 작동되는걸 막을 수 있다.
리시버가 트렌지스터 형태로 돼있어서 그런지 잡음을 막기 힘들다.

참고 : 내가 쓴 건 대부분 약자로 쓴거다.
te=temp
spd=speed
sw=switch 
ang=angle
등등..

위에 있는 코드는 리모컨으로 모드를 끄고 킬 수 있는 녀석이다.
예를 들어 특정 버튼을 누르면 라인트레이서 모드를 끄고 킬 수 있는 것이다
한번 입력하면 켜지고 다시 누르면 꺼진다.
*/



void loop() {
  Fv = analogRead(Fs); Bv = analogRead(Bs); Lv = analogRead(Ls); Rv = analogRead(Rs);
  if (irrecv.decode(&res))  {
    Serial.println(res.value, HEX);
    sw(res.value);
    mr(spd);
    irrecv.resume();

    
    if (res.value == 0xFFFFFFFF) {
      sw(te);
    }
  }

  if (linesw == 1) {
    linetracer();
  }

  if (f1 == 1) {
    delay(1000);
    sp();
  }

  if (f2 == 1) {
    delay(500);
    Serial.print("T = ");
    Serial.print(T);
    Serial.println(" us");
    Serial.print("D = ");
    Serial.print(L);
    Serial.println(" cm");
  }

  if (L == 5) {
    st();
  }

  digitalWrite(tr, HIGH);
  delayMicroseconds(2);
  digitalWrite(tr, LOW);
  delayMicroseconds(10);
  digitalWrite(tr, HIGH);
  T = pulseIn(ec, HIGH);
  L = T / (float)58.2;
}

long int sw(long int val) {
  switch (val) {
    case 0xFD00FF:  // turns on UUT power
      Serial.println("POWER (stop)");
      servo.write(100); st();
      te = val;
      break;

    case 0xFD40BF:  // FUNC/STOP turns off UUT power
      Serial.println("FUNC/STOP");
      switch (linesw) {
        case 0:
          linesw = 1;
          Serial.println("linetracer on");
          break;
        case 1:
          linesw = 0;
          Serial.println("linetracer off");
          break;
          te = 0;
      }
      break;

    case 0xFD20DF:  // |<< ReTest failed Test
      if (ang < 150) {
        servo.write(ang = ang + 3);
      }
      Serial.print("|<<");
      Serial.print(ang - 100);
      Serial.println(")");
      te = val;
      break;

    case 0xFDA05F:  // >|| Test
      servo.write(100);
      Serial.println(">|| (str)");
      te = val;
      break;

    case 0xFD609F:  // >>| perform selected test number
      if (ang > 50) {
        servo.write(ang = ang - 3);
      }
      Serial.print(">>| (");
      Serial.print(ang - 100);
      Serial.println(")");
      te = val;
      break;

    case 0xFD807F:  // VOL+ turns on individual test beeper
      if (spd < 248) {
        spd = spd + 2;
      }
      Serial.print("VOL+ (");
      Serial.print((spd - 128) * 2);
      Serial.println(")");
      te = val;
      break;

    case 0xFD906F:  // VOL- turns off individual test beeper
      if (spd > 8) {
        spd = spd - 2;
      }
      Serial.print("VOL- (");
      Serial.print((spd - 128) * 2);
      Serial.println(")");
      te = val;
      break;

    case 0xFFFFFFFF: // hold
      break;


    default:
      {
        te = 0;
      }
      delay(5);

      if (spd == 0) {
        delay(500);
      }
  }
}