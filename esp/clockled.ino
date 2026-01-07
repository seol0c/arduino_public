#include <WiFi.h>
#include <time.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>

// ===== WiFi =====
const char* WIFI_SSID     = "EM";
const char* WIFI_PASSWORD = "starcraft";

// ===== OLED =====
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C   
#define SDA_PIN 6
#define SCL_PIN 7

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ===== AHT20 =====
Adafruit_AHTX0 aht;
sensors_event_t humidity, temp;
bool aht_ok = false;

// ===== Time (KR UTC+9) =====
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 9 * 3600;
const int   daylightOffset_sec = 0;

const char* WEEKDAY_VI[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

String two(int v){ return (v<10) ? "0"+String(v) : String(v); }

void drawCentered(const String& text, int16_t y, uint8_t size=1){
  display.setTextSize(size);
  int16_t x1,y1; uint16_t w,h;
  display.getTextBounds(text, 0, y, &x1,&y1,&w,&h);
  display.setCursor((SCREEN_WIDTH - w)/2, y);
  display.print(text);
}

void wifiConnect(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  uint32_t t0 = millis();
  while (WiFi.status() != WL_CONNECTED && millis()-t0 < 20000){
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    drawCentered("Connecting to Wifi", 20, 1);
    drawCentered("...", 36, 1);
    display.display();
    delay(300);
  }
}

void setup(){
  Wire.begin(SDA_PIN, SCL_PIN);

  // OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    for(;;) delay(1000);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  drawCentered("ESP32-C3 + AHT20", 22, 1);
  display.display();
  delay(800);

  // AHT20
  aht_ok = aht.begin();
  display.clearDisplay();
  if(aht_ok) drawCentered("AHT20 OK", 24, 1);
  else       drawCentered("AHT20 FAIL", 24, 1);
  display.display();
  delay(600);

  // WiFi + NTP
  wifiConnect();
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop(){
  static uint32_t lastDisp = 0, lastSens = 0;
  static float T = NAN, H = NAN;   

  
  if(millis() - lastSens > 2000){
    lastSens = millis();
    if(aht_ok && aht.getEvent(&humidity, &temp)){
      T = temp.temperature;   // °C
      H = humidity.relative_humidity; // %
    } else {
      T = NAN; H = NAN;       
    }
  }

  
  if(millis() - lastDisp > 200){
    lastDisp = millis();
    display.clearDisplay();

   
    struct tm ti;
    bool ok = getLocalTime(&ti);
    if(ok){
      String timeStr = two(ti.tm_hour)+":"+two(ti.tm_min)+":"+two(ti.tm_sec);
      String dateStr = String(WEEKDAY_VI[ti.tm_wday]) + "  " +
                       String(ti.tm_year+1900)+"/"+two(ti.tm_mon+1)+"/"+two(ti.tm_mday);//    two(ti.tm_mday)+"/"+two(ti.tm_mon+1)+"/"+String(ti.tm_year+1900);
      drawCentered(timeStr, 12, 2);
      drawCentered(dateStr, 38, 1);
    }else{
      drawCentered("Synchronizing...", 26, 1);
    }

    
    display.drawLine(0, 50, 127, 50, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 54);
    if(isnan(T)) display.print("T: --.-C");
    else { display.print("T: "); display.print(T, 1); display.print("C"); }

    String humStr = isnan(H) ? "H: ---%" : ("H: " + String(H, 0) + "%");
    int16_t x1,y1; uint16_t w,h;
    display.getTextBounds(humStr, 0, 54, &x1,&y1,&w,&h);
    display.setCursor(SCREEN_WIDTH - w, 54);
    display.print(humStr);

    display.display();
  }
}
