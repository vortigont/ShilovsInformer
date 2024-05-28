#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <WiFi.h>
#include <GyverNTP.h>
#include <GyverPortal.h>
#include <MD_UISwitch.h>
#include <iarduino_RTC.h>
#include <ArduinoJson.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_BMP085.h>
#include "Adafruit_BME280.h"
#include <Adafruit_AHTX0.h>
#include <GyverHTU21D.h>
#include <UnixTime.h>
#include <HTTPClient.h>
#include <DFRobotDFPlayerMini.h>
#include "6bite_rus.h"
#include "5bite_rus.h"
#include "5abite_rus.h"
#include "ef.h"
#define SEALEVELPRESSURE_HPA (1013.25)
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//==============================================================
//Пины матрицы MAX7219 esp32
#define CLK_PIN   19  // or SCK
#define DATA_PIN  18  // or MOSI
#define CS_PIN    17  // or SS
int MAX_DEVICES = 4;// количество модулей!!!
GyverNTP ntp(3,60);// часовой пояс-3, время обновления -60сек.
int Z = 3;// пин подключения мр3 модуля
//============================================================
TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;
HardwareSerial hwSerial(1);
DFRobotDFPlayerMini dfPlayer;
iarduino_RTC watch(RTC_DS3231);
static uint32_t tmrM,tmrP,tmrN,tmrV,tmrA,tmrW,tmrBud;
int yar = 1,oldyar = 1, chrift = 0;
int sk = 20;
bool pog = false;
String POGODA = "";
String text1 = "";
char Buf[20];
char Buf1[70];
char Buf2[300];
char Buf4[250];
char Buf3[] = "     Нет погоды";
char Buf5[] = "     Нет прогноза погоды";
char IP[24] = "";
char WIFI[] = "   Подключаемся к wi-fi";
char POGSER[] = "   Погода?";
char Tdwf[] = "     Подключитесь к точке доступа WiFi Config по адресу 192.168.4.1";
int y = 0, z = 0;
int location_code;
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
HTTPClient http;
bool flagToch = false;
bool zapros = false;
int q = 1;
//будильник
bool BUD,BUD1,BUD2,BUD3,BUD4,BUD5,BUD6,BUD7;
char Buf7[] = "@";
bool flagBudilnik = false;
int hBud,hBud1,hBud2,hBud3,hBud4,hBud5,hBud6,hBud7;
int mBud,mBud1,mBud2,mBud3,mBud4,mBud5,mBud6,mBud7;
int Pap,PaB1,PaB2,PaB3,PaB4,PaB5,PaB6,PaB7;
//плеер мр3
int Y = 10;
bool flagGV = true;
int MG = 0, Pn = 11;
//ночной
bool MNR = false;
bool flagNR = false;
int hNon = 22;
int mNon = 0;
int sNon = 0;
int hNoff = 6;
int mNoff = 0;
int sNoff = 0;
//RTC
bool flagRTC = false;
bool swtRTC = false;
//датчики
char Bufthp[250];
GyverHTU21D htu;
Adafruit_AHTX0 aht;
Adafruit_Sensor *aht_humidity, *aht_temp;
Adafruit_BME280 bme;
Adafruit_BMP280 bmp;
Adafruit_BMP085 bmp180;
bool M1, M2, M3, M4, M5;
int wett;
int wetp;
int weth;
int humath;
bool pressSys = 1;
float tempGY = 0;
float humGY = 0;
float tempBme = 0;
float humBme = 0;
float pressBme = 0;
float altBme = 0;
float humAT = 0;
float tempAT = 0;
float tempBmp = 0;
float pressBmp = 0;
float altBmp = 0;
bool bmp280 = false;
bool BMP180 = false;
String Domtemhumpres;
int CorTemp = 0;// коррекция температуры
int  corrPress = 0;// коррекция давления
int CorHum = 0;// коррекция влажности
//валюта
char BufVal[250];
bool flagValute = false;
float usd;
float eur;
float byn;
float uah;
String valutedok = "";
bool valu = false;
//Афоризм
String aforizm;
String location_anek = " ";
String location_awt = " ";
bool flagAforizm = false;
char Bufafor[500];
//погода
bool flagPogoda = false;
String Text = "";
String Text1 = "";
String weekDay[] = {"", "понедельник", "вторник", "среда", "четверг", "пятница", "суббота", "воскресенье"};
String months[] = {"","января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря"};
String POG = "";
String pogodaS = "";
String pogodaP = ""; 
String jsonConfig = "{}";
bool printCom = true, modeeff = true, flagzapros = false;;
int mod1=0;
int x = 0;

String gorod ="Гомеле",latitude = "52.43",longitude = "30.97",api_key = "your_key";
String units = "metric";  // or "imperial"
String language = "ru";   // See notes tab
char ssid[20];
char pass[20];
String wssid,wpass;


static textPosition_t just = PA_CENTER;
static uint8_t i = 0;   // text effect index
static uint8_t j = 0;   // text justification index
static uint8_t modDate = 0;
static uint8_t  curFX = 6;
// Global data
struct sCatalog
{
  textEffect_t  effect;   // text effect to display
  const char *  psz;      // text string nul terminated
  uint16_t      speed;    // speed multiplier of library default
  uint16_t      pause;    // pause multiplier for library default
};
sCatalog catalog[] =
{
  { PA_NO_EFFECT, Buf, 4, 0},
  //{ PA_PRINT, Buf, 1, 1},
  //{ PA_SCROLL_UP, Buf, 15, 1},
 // { PA_SCROLL_DOWN, Buf, 15, 1 },
 // { PA_SCROLL_LEFT, Buf, 15, 1 },
 // { PA_SCROLL_RIGHT, Buf, 15, 1 },
#if ENA_SPRITE
  { PA_SPRITE, Buf, 20, 1 },
#endif
#if ENA_MISC
  { PA_SLICE, Buf, 5, 1 },
  { PA_MESH, Buf, 40, 1 },
  { PA_FADE, Buf, 40, 1 },
  { PA_DISSOLVE, Buf, 20, 1 },
  { PA_BLINDS, Buf, 20, 1 },
  { PA_RANDOM, Buf, 10, 1 },
#endif
#if ENA_WIPE
  { PA_WIPE, Buf, 15, 1 },
  { PA_WIPE_CURSOR, Buf, 12, 1 },
#endif
#if ENA_SCAN
  { PA_SCAN_HORIZ, Buf, 12, 1 },
  { PA_SCAN_HORIZX, Buf, 12, 1 },
  { PA_SCAN_VERT, Buf, 10, 1 },
  { PA_SCAN_VERTX, Buf, 10, 1 },
#endif
#if ENA_OPNCLS
  { PA_OPENING, Buf, 10, 1 },
  { PA_OPENING_CURSOR, Buf, 12, 1 },
  { PA_CLOSING, Buf, 10, 1 },
  { PA_CLOSING_CURSOR, Buf, 12, 1 },
#endif
#if ENA_SCR_DIA
  { PA_SCROLL_UP_LEFT, Buf, 20, 1 },
  { PA_SCROLL_UP_RIGHT, Buf, 20, 1 },
  { PA_SCROLL_DOWN_LEFT, Buf, 20, 1 },
  { PA_SCROLL_DOWN_RIGHT, Buf, 20, 1 },
#endif
#if ENA_GROW
  { PA_GROW_UP, Buf, 20, 1 },
  { PA_GROW_DOWN, Buf, 20, 1 },
#endif
};
struct 
{
  const uint8_t *data;
  uint8_t width;
  uint8_t frames;
} 
sprite[] =
{
  { walker, W_WALKER, F_WALKER },
  { invader, W_INVADER, F_INVADER },
  { chevron, W_CHEVRON, F_CHEVRON },
  { heart, W_HEART, F_HEART },
  { arrow1, W_ARROW1, F_ARROW1 },
  { steamboat, W_STEAMBOAT, F_STEAMBOAT },
  { fireball, W_FBALL, F_FBALL },
  { rocket, W_ROCKET, F_ROCKET },
  { roll2, W_ROLL2, F_ROLL2 },
  { pacman2, W_PMAN2, F_PMAN2 },
  { lines, W_LINES, F_LINES },
  { roll1, W_ROLL1, F_ROLL1 },
  { sailboat, W_SAILBOAT, F_SAILBOAT },
  { arrow2, W_ARROW2, F_ARROW2 },
  { wave, W_WAVE, F_WAVE },
  { pacman1, W_PMAN1, F_PMAN1 }
};

GyverPortal portal;

void build1() {
  String s;
  BUILD_BEGIN(s);
  GP.THEME(GP_DARK);
  GP.TITLE("📶 𝕮𝖑𝖔𝖈𝖐", "font30 fontcyan_000000");
  GP.FORM_BEGIN("/login");
  GP.TEXT("txtssid", "Login", ssid, "font20 fontyellow_c79536"); GP.BREAK();
  GP.TEXT("txtpass", "Password", pass, "font20 fontyellow_c79536"); GP.BREAK();
  GP.SUBMIT("💾 СОХРАНИТЬ ", "backgroundred_a5381b widthauto height30 font20 fontblue_000000");
  GP.FORM_END();
  BUILD_END();
}

void conekt_wifi()
{
  Serial.print("Connect to: ");
  Serial.println(ssid);
  Serial.println(pass);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
   while(WiFi.status() != WL_CONNECTED) {
    P.print("wi-fi");
    if (P.displayAnimate()) // animates and returns true when an animation is completed
   {
   P.displayText(WIFI, just, 20, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
   }
    delay(500);
    x++;
    if(x == 25)loginPortal(); 
  }
  Serial.println("Connected! Local IP: ");
  P.print("|");
  delay(1000);
  Serial.println(WiFi.localIP());
  Serial.println("");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  ip.toString().toCharArray(IP,24);
   if (P.displayAnimate()) // animates and returns true when an animation is completed
   {
   P.displayText(IP, just, 50, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
   }
   delay(1000);
  portal.attachBuild(build);
  portal.attach(Portal);
  portal.start();
 // portal.log.start(30);
  delay(1000);
  int lok = 0;
  while(lok<2){
  if (P.displayAnimate()) // animates and returns true when an animation is completed
   {
   P.displayText(POGSER, just, 50, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
   lok++;
   }
  }
  printCurrentWeather();
  delay(1000);
   if(location_code != 0){
    P.print("yes!");
     }else{
    P.print("no!");  
  }
  delay(1000);
  ntp.begin();
  Val();
  Anek();
  tmrM = millis();
  tmrP = millis();
  tmrN = millis();
  tmrV = millis();
  tmrW = millis(); 
   xTaskCreatePinnedToCore(
    Task1code
    ,  "Task1"
    ,  10000
    ,  NULL
    ,  5
    ,  &Task1
    , 1);
   xTaskCreatePinnedToCore(
    Task2code
    ,  "Task2"
    ,  20000
    ,  NULL
    ,  2
    ,  &Task2
    , 1); 
    xTaskCreatePinnedToCore(
    Task3code
    ,  "Task3"
    ,  10000
    ,  NULL
    ,  7
    ,  &Task3
    , 1);       
}
void loginPortal() {
  Serial.println("Portal start");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("WiFi Config");
  int lon = 0;
  while(lon<2){
  if (P.displayAnimate()) // animates and returns true when an animation is completed
   {
   P.displayText(Tdwf, just, 50, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
   lon++;
   }
  }
  
  portal.attachBuild(build1);
  portal.start();
  portal.attach(action);
  x = 0;
  while (portal.tick());
}

void action() {
    if (portal.uri() == "/login"){
    wssid = portal.getString("txtssid");
    wpass = portal.getString("txtpass"); 
    wssid.toCharArray(ssid, 20);
    wpass.toCharArray(pass, 20);  
    saveConfig();            
    WiFi.softAPdisconnect();
    ESP.restart();
  }
}

void setup() {
  hwSerial.begin(9600, SERIAL_8N1, 4, Z);// TX,RX
  Serial.begin(115200);
   if (!SPIFFS.begin()) {
    Serial.println("Ошибка инициализации SPIFFS!");
    while (1) yield(); // Оставайся здесь
  }
  loadConfig();
  watch.begin(); 
  dfPlayer.begin(hwSerial);
  dfPlayer.volume(Y);
  dfPlayer.setTimeOut(100);
  dfPlayer.outputDevice(DFPLAYER_DEVICE_SD);
   bool status;
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Did not find BME280 sensor!");
  } else {
    Serial.println("YES!!! find BME280 sensor!");
    M1 = true;
    Serial.println ("Mod = 1");
  }
  if (bmp.begin()) {
    if (printCom) Serial.println("YES!!! find BMP280 sensor!");
    M2 = true;
    Serial.println ("Mod = 3");
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);
    bmp280 = true;
    sensorsBmp280();
  } else if (printCom) Serial.println("Did not find BMP280 sensor!");
  if (bmp180.begin()) {
    if (printCom) Serial.println("YES!!! find BMP180 sensor!");
    M3 = true;
    Serial.println ("Mod = 4");
    BMP180 = true;
    sensorsBmp180();
  } else if (printCom) Serial.println("Did not find BMP180 sensor!");
  if (aht.begin()) {
    Serial.println("AHT10 or AHT20 found");
    M4 = true;
    Serial.println ("Mod = 2");
    aht_temp = aht.getTemperatureSensor();
    aht_temp->printSensorDetails();
    aht_humidity = aht.getHumiditySensor();
    aht_humidity->printSensorDetails();
  }
  Serial.println("Did not find AHT10 or AHT20 sensor!");

  if (!htu.begin()) {
    Serial.println(F("HTU21D error"));
  } else {
    Serial.println(F("HTU21D YES!!!"));
    getsensGY21();
    M5 = true;
  }
  P.begin();
  catalog[i].speed *= P.getSpeed()*3;
  catalog[i].pause *= 500;
  P.setIntensity(yar) ;
  switch(chrift){
      case 0:P.setFont(_5bite_rus);break;
      case 1:P.setFont(_5abite_rus);break;
      case 2:P.setFont(_6bite_rus);break;
     }
  wssid.toCharArray(ssid, 20);
  wpass.toCharArray(pass, 20); 
  Serial.println("coneft wifi");
  conekt_wifi();
}
void Task1code(void *pvParameters)
{
  for (;;)
  {
  portal.tick();
  ntp.tick();
  if (millis() - tmrW >= 30000 && WiFi.status() != WL_CONNECTED) {
  tmrW = millis();  
  Conekted();  
  }else{
  Time();
  Date();
  }
  NR();
   vTaskDelay(10);
  }
}
void Task2code(void *pvParameters)
{
  for (;;)
  {
    switch(modDate){
      case 1:Mod1();break;
      case 2:Mod2();break;
      case 3:Mod3();break;
      case 4:Mod4();break;
      case 5:Mod5();break;
      case 6:Mod6();break;
      case 7:Mod7();break;
    }
    if (ntp.minute() == 0 && ntp.second() == 0 && flagGV == true) {
      switch (MG) {
        case 0: Pn = 11;break;
        case 1: Pn = 12;break;
        case 2: Pn = 13;break;
        }
      dfPlayer.volume(Y);
      dfPlayer.playFolder(Pn, ntp.hour());
    }
    vTaskDelay(1);
  }
}
void Task3code(void *pvParameters)
{
  for (;;)
 {
   if (millis() - tmrN >= 600000 && zapros == true){tmrN = millis();printCurrentWeather();}
   if (millis() - tmrV >= 240000 && zapros == true){tmrV = millis();Val();} 
   if (millis() - tmrA >= 120000 && zapros == true){tmrA = millis();Anek();}
   switch(chrift){
      case 0:P.setFont(_5bite_rus);break;
      case 1:P.setFont(_5abite_rus);break;
      case 2:P.setFont(_6bite_rus);break;
     }
   vTaskDelay(1);
  }
}

void loop(void)
{
   if (P.displayAnimate())// while (!(P.displayAnimate()));
  {
    P.setIntensity(yar) ;
    if(q>=7)q=1;
    Time();
    if (millis() - tmrM >= sk*2000 && flagNR == false){
      tmrM = millis();
      modDate=q;
      zapros = false;
      }else{
       zapros = true;
       if (M1 == true || M2 == true || M3 == true || M4 == true || M5 == true)getSens();  
      }
    if (i == ARRAY_SIZE(catalog)){i = 0;y = 0;}  
    if(i == ENA_SPRITE){P.setSpriteData(sprite[curFX].data, sprite[curFX].width, sprite[curFX].frames,sprite[curFX].data, sprite[curFX].width, sprite[curFX].frames);} 
    P.displayText(Buf, just, catalog[i].speed, catalog[i].pause, catalog[i].effect, catalog[i].effect);
     Budilok();
     if(i!= 0)y++;
     if(y == 1){i = 0;y = 0;}
     if (millis() - tmrP >= 10000 && flagNR == false){tmrP = millis();i=i+z;z++;} 
     if(z>1){z=0;curFX++;}//28
     if(curFX>15)curFX=0;
     }
  
}
void Mod1()
{
      P.displayText(Buf1, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
      P.displayReset();
      q++;
      modDate=0;
}
void Mod2()
{
    if (M1 == true || M2 == true || M3 == true || M4 == true || M5 == true){
       P.displayText(Bufthp, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
       P.displayReset();
       q++;
      modDate=0;
      }else{
      q++;
      modDate=0;
   }   
}
void Mod3()
{
  if(flagPogoda == true){
     if(location_code != 0){
         P.displayText(Buf2, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
         }else{
         P.displayText(Buf3, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
         }
      q++;
      modDate=0;
   }else{
      q++;
      modDate=0;
   }
  
}
void Mod4()
{
    if(flagPogoda == true){
     if(location_code != 0){
         P.displayText(Buf4, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
         }else{
         P.displayText(Buf5, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
         }
      q++;
      modDate=0;
     }else{
      q++;
      modDate=0;
   }   
  
}
void Mod5()
{
    if(flagValute == true){
       P.displayText(BufVal, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
       P.displayReset();
       q++;
      modDate=0;
      }else{
      q++;
      modDate=0;
   }   
}
void Mod6()
{
    if(flagValute == true){
       P.displayText(Bufafor, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
       P.displayReset();
       q++;
      modDate=0;
      }else{
      q=q+2;
      modDate=0;
   }   
}
void Time()
{
  text1 = "";
  text1 += ntp.hour();
  if (flagToch == false) {
    if (ntp.second() % 2 == 0)
    {
      text1 += ":";
    } else {
      text1 += " ";
    }
  } else {
    if (ntp.second() % 2 == 0)
    {
      text1 += "$";
    } else {
      text1 += "&";
    }
  }
  if (ntp.minute() < 10)text1 += "0";
  text1 += ntp.minute();
  text1.toCharArray(Buf, 20);
}
void Date()
{
  String Textday="";
  Textday += "       ";
  Textday += ntp.day();
  Textday += " ";
  Textday += months[ntp.month()];
  Textday += " ";
  Textday += ntp.year();
  Textday += " ";
  Textday += "года";
  Textday += " ";
  Textday += weekDay[ntp.dayWeek()];
  Textday.toCharArray(Buf1, 70);
}
