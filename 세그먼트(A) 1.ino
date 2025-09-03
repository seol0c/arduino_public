/*세그먼트는 그저 8개의 LED를 각각 제어하여 숫자를 나타낼 뿐입니다.
  각각 핀 번호를 데이터시트를 참조하여 a,b,c등으로 부르면(변수 설정) 다루기 쉽습니다.
  여기서 사용한 코드는 5611-A타입에 대한 것입니다.
  가운데 핀에 GND를 입력하며 LOW신호(0)에서 불이 꺼지고 HIGH신호(1)에서 불이 켜집니다.
  5611-B타입은 가운데 핀에 5V를 연결하며 HIGH신호(1)에서 불이 꺼집니다. */

int a = 9;
int b = 8;
int c = 5;
int d = 6;
int e = 7;
int f = 10;
int g = 11;
int dp = 4;

void setup() {
  pinMode(a, OUTPUT); //a를 출력모드로 설정
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);
}

/* HIGH와 LOW를 1,0으로 표현할 수 있습니다.
  간결하지만 의미 파악이 힘들기 때문에 평소에 잘 사용하지 않습니다.
  하지만 여러 LED를 동시에 제어하는 경우 1,0으로 표현하는 게 더 유리할 수도 있습니다. */

void loop() {
  digitalWrite(a, 0); //모두 꺼짐(5611-A타입)
  digitalWrite(b, 0);
  digitalWrite(c, 0);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 0);
  digitalWrite(g, 0);
  digitalWrite(dp, 0);
  delay(1000);

  digitalWrite(a, 0); //숫자 1 표시
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 0);
  digitalWrite(g, 0);
  digitalWrite(dp, 0);
  delay(1000);

  digitalWrite(a, 1); //숫자 2 표시
  digitalWrite(b, 1);
  digitalWrite(c, 0);
  digitalWrite(d, 1);
  digitalWrite(e, 1);
  digitalWrite(f, 0);
  digitalWrite(g, 1);
  digitalWrite(dp, 0);
  delay(1000);

  digitalWrite(a, 1); //숫자 3 표시
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 0);
  digitalWrite(f, 0);
  digitalWrite(g, 1);
  digitalWrite(dp, 0);
  delay(1000);

  digitalWrite(a, 0); //숫자 4 표시
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 1);
  digitalWrite(g, 1);
  digitalWrite(dp, 0);
  delay(1000);

  digitalWrite(a, 1); //숫자 5 표시
  digitalWrite(b, 0);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 0);
  digitalWrite(f, 1);
  digitalWrite(g, 1);
  digitalWrite(dp, 0);
  delay(1000);
}