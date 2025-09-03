//wifi scan 예제를 통해 모듈이 이상 없는지 먼저 확인
//wifi가 공개된 상태에서만 연결할 수 있음을 확인

#include <ESP8266WiFi.h>

const char* ssid = "0c";          //와이파이 SSID
const char* password = "0629515067";  //와이파이 비밀번호

int led = 16;           // GPIO16는 NodeMCU의 내장 led임
WiFiServer server(80);  //대부분 80번 포트 사용

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW); //내장 led는 low에서 켜짐

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);                     //wifi에 연결함을 시리얼모니터에 출력

  WiFi.begin(ssid, password);               //wifi 연결 시작(WL_CONNECTED라는 값을 반환)
  while (WiFi.status() != WL_CONNECTED) {   //와이파이에 연결될때까지(연결 상태, 8개의 리턴값 / STATUS와 WL_CONNECTED 값 비교)
    delay(500);
    Serial.print(".");                      //"."을 출력(줄바꿈하지 않음) 연결될 때까지 ... 출력
  }
  Serial.println("");
  Serial.println("WiFi connected");         //연결되면(While을 벗어나면) 줄바꾸고 연결됨을 출력

  server.begin();                           //NodeMCU를 웹서버로 사용 시작
  Serial.println("Server started");

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());             //시리얼모니터에 할당된 가상 ip주소를 출력함
  Serial.println("/");                      //이 주소로 들어오면 NodeMCU의 웹서버로 접속됨
}

void loop() {
  WiFiClient client = server.available();     // Client가 들어오는지 체크
  if (!client) {                //Client가 접속하지 않으면
    return;                     //return(종료)
  }

  Serial.println("new client"); //위의 if문을 건너뛰면(Client가 접속하면) 문구 출력 후 줄바꿈
  while (!client.available()) { //Client를 사용할 수 있을 때까지(어떤 데이터를 줄 때까지)
    delay(1);                   //1ms의 딜레이를 반복
  }

  String request = client.readStringUntil('\r');  //전송받은 데이터를 \r까지 request에 저장
  Serial.println(request);                        //'\r'은 HTTP/1.1을 의미(첫번째 줄)
  client.flush();                                 //Client에 남아 있는 데이터를 삭제
  /*나중에 IP주소로 들어가면 시리얼 모니터에 GET/LED=ON HTTP/1.1 등으로 표시되고 이것의 의미는
    GET 방식 사용 / /LED=ON이라는 요청이 들어옴 / Client.println("HTTP/1.1 200OK");로 판단한 HTTP 응답
    위의 형식으로 출력됨*/

  /* 아래부터는 요청(request)에 의해 동작하는 부분
     get 방식을 사용하므로 request.indexOf을 사용함
     가상 IP에 만들어놓은 웹브라우저 버튼을 눌러 request가 들어오면 입력 버퍼를 확인하여
     두 개의 if문을 통해 내장 LED를 제어함.
     기본 버퍼는 -1인 상태이며 request가 들어오면 -1이 아닌 다른 값이 들어오므로
     조건문을 !=-1로 하여 버퍼가 -1이 아닌 경우 동작하도록 함 */

  int value = LOW;                          //value는 상태를 출력하는 변수로 설정
  if (request.indexOf("/LED=ON") != -1)  {  //"/LED=ON"의 요청이 들어오면
    digitalWrite(led, HIGH);                //LED를 켜고
    value = HIGH;                           //value 값을 HIGH로 설정
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(led, LOW);
    value = LOW;
  }

  //아래부터는 응답을 확인하는 구간(html 형식으로 웹페이지에서 확인)
  client.println("HTTP/1.1 200 OK");        //HTTP 상태 코드(200 OK는 상태가 정상임을 뜻함)
  client.println("Content-Type: text/html");  //html 형태를 text로 작성. http 요청 헤더에 사용자의
  client.println("");                         //입력을 전송하므로 어떤 형식으로 입력하는지 설정
  client.println("<!DOCTYPE HTML>");      //html5 형식을 사용한다고 선언
  client.println("<html>");           //웹브라우저 시작(</html>과 쌍을 이룸)

  client.print("LED is now: ");     //LED 상태를

  if (value == HIGH) {        //value 값이 HIGH이면 ON, 그렇지 않으면 OFF라고 출력
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>"); //줄바꿈
  client.println("<a href=\"/LED=ON\"\"><button>On </button></a>"); //버튼 생성
  client.println("<a href=\"/LED=OFF\"\"><button>Off </button></a><br />");
  client.println("</html>");  //웹브라우저 끝

  /* <a>는 링크를 만들기 위한 태그이며 기본적으로 href 속성을 갖고 이동할 페이지 주소를 적어주면 됨
     get 방식은 url을 입력하여 입력값을 판별하므로
     <a href="/LED=ON"></a>는 /LED=ON이라는 주소로 가는 링크를 만들겠다는 의미
     IDE를 통해 html 문서를 작성하므로 위의 내용을 문자열(string) 선언 하는 과정에서 ""의 범위를 제대로
     설정하기 위해 사이사이에 \을 넣음(\을 빼면 문자열로 취급되지 않는 문제가 발생)
     <button>은 버튼을 만드는 태그로서 <button>On </button>은 On이라는 버튼을 생성함
     즉,
     <a href="/LED=ON"></a><button>On </button></a>은
     누르면 /LED=ON 페이지로 이동하는 "On"이라고 써진 버튼을 만든다는 의미. <br />은 줄바꿈 */

  delay(1); //1ms 대기
  Serial.println("Client disonnected"); //get 요청이 끝났으므로 메세지 출력
  Serial.println("");

}

/* 출력 후 시리얼모니터에서 할당된 IP주소로 들어가면 LED 초기값과 버튼이 있음
   favicon.ico은 웹 브라우저 주소창에 표시되는 아이콘(자물쇠, 느낌표 등)
   On 버튼을 누르면 url에 /LED=ON이 추가되고 시리얼 모니터에 GET/LED=ON HTTP/1.1 등이 표시됨 */
