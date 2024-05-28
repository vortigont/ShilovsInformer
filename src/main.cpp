#include "main.h"
#include <LittleFS.h>

#include <MD_MAX72xx.h>
#include <SPI.h>
#include <WiFi.h>
#include <MD_UISwitch.h>
#include <ArduinoJson.h>
#include "6bite_rus.h"
#include "5bite_rus.h"
#include "5abite_rus.h"
#include "ef.h"

#include "pogoda.h"
#include "web_services.h"

//==============================================================
//Пины матрицы MAX7219 esp32
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CLK_PIN   19  // or SCK
#define DATA_PIN  18  // or MOSI
#define CS_PIN    17  // or SS
int MAX_DEVICES = 4;// количество модулей!!!
int Z = 3;// пин подключения мр3 модуля

//============================================================

GyverNTP ntp(3,60);// часовой пояс-3, время обновления -60сек.

// rtos tasks (pretty useless)
TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;

HardwareSerial hwSerial(1);
//плеер мр3
DFRobotDFPlayerMini dfPlayer;
int dfp_volume = 10;

static uint32_t tmrM,tmrP,tmrN,tmrV,tmrA,tmrW,tmrBud;
int yar = 1, oldyar = 1, chrift = 0;
int sk = 20;
bool pog = false;

String textStringBuff1 = "";
char Buf[20];
// строка домашние сенсоры
char home_sens_buff[250];
char dateStringBuff[70];
char IP[24] = "";
char WIFI[] = "   Подключаемся к wi-fi";
char POGSER[] = "   Погода?";
char Tdwf[] = "     Подключитесь к точке доступа WiFi Config по адресу 192.168.4.1";
int y = 0, z = 0;
int location_code;

MD_Parola parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


bool flagToch = false;
bool zapros = false;
int unknown_q = 1;


char Buf7[] = "@";
bool flagGV = true;
int MG = 0, Pn = 11;
//ночной
bool someNightModeVar = false;
bool nightModeFlag = false;
int hNon = 22;
int mNon = 0;
int sNon = 0;
int hNoff = 6;
int mNoff = 0;
int sNoff = 0;


//валюта
char BufVal[250];
bool flagValute = false;
bool valu = false;
char aforizm_buff[500];
String Text = "";
String Text1 = "";
String POG = "";
String jsonConfig = "{}";

// какие-то флаги
bool printCom = true, modeeff = true, flagzapros = false;;
int mod1=0;
int x = 0;

String wssid, wpass;


textPosition_t just = PA_CENTER;
static uint8_t i = 0;   // text effect index
static uint8_t j = 0;   // text justification index
uint8_t modDate = 0;
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

// forward declarations
void Task1code(void *pvParameters);
void Task2code(void *pvParameters);
void Task3code(void *pvParameters);
void get_wifi_creds();
void mkTime();
void mkDate();
void Budilok();
void nightMode();




void build1() {
  String s;
  BUILD_BEGIN(s);
  GP.THEME(GP_DARK);
  GP.TITLE("📶 𝕮𝖑𝖔𝖈𝖐", "font30 fontcyan_000000");
  GP.FORM_BEGIN("/login");
  GP.TEXT("txtssid", "Login", wssid.c_str(), "font20 fontyellow_c79536"); GP.BREAK();
  GP.TEXT("txtpass", "Password", wpass.c_str(), "font20 fontyellow_c79536"); GP.BREAK();
  GP.SUBMIT("💾 СОХРАНИТЬ ", "backgroundred_a5381b widthauto height30 font20 fontblue_000000");
  GP.FORM_END();
  BUILD_END();
}

void conekt_wifi()
{
  Serial.print("Connect to: ");
  Serial.println(wssid.c_str());
  Serial.println(wpass.c_str());
  WiFi.mode(WIFI_STA);
  WiFi.begin(wssid.c_str(), wpass.c_str());
   while(WiFi.status() != WL_CONNECTED) {
    parola.print("wi-fi");
    if (parola.displayAnimate()) // animates and returns true when an animation is completed
   {
   parola.displayText(WIFI, just, 20, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
   }
    delay(500);
    x++;
    if(x == 25)loginPortal(); 
  }
  Serial.println("Connected! Local IP: ");
  parola.print("|");
  delay(1000);
  Serial.println(WiFi.localIP());
  Serial.println("");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  ip.toString().toCharArray(IP,24);
   if (parola.displayAnimate()) // animates and returns true when an animation is completed
   {
   parola.displayText(IP, just, 50, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
   }
   delay(1000);
  portal.attachBuild(gv_portal_build);
  portal.attach(gv_portal_run);
  portal.start();
 // portal.log.start(30);
  delay(1000);
  int lok = 0;
  while(lok<2){
  if (parola.displayAnimate()) // animates and returns true when an animation is completed
   {
   parola.displayText(POGSER, just, 50, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
   lok++;
   }
  }
  //printCurrentWeather();
  delay(1000);

   if(location_code != 0){
    parola.print("yes!");
     }else{
    parola.print("no!");  
  }
  delay(1000);
  ntp.begin();
  currencyRates();
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
  if (parola.displayAnimate()) // animates and returns true when an animation is completed
   {
   parola.displayText(Tdwf, just, 50, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
   lon++;
   }
  }
  
  portal.attachBuild(build1);
  portal.start();
  portal.attach(get_wifi_creds);
  x = 0;
  while (portal.tick());
}

void get_wifi_creds() {
    if (portal.uri() == "/login"){
    wssid = portal.getString("txtssid");
    wpass = portal.getString("txtpass"); 
    saveConfig();            
    WiFi.softAPdisconnect();
    ESP.restart();
  }
}

// Arduino setup
void setup() {
  hwSerial.begin(9600, SERIAL_8N1, 4, Z);// TX,RX
  Serial.begin(115200);

  LittleFS.begin(true);
/*
  if (!SPIFFS.begin()) {
    Serial.println("Ошибка инициализации SPIFFS!");
    while (1) yield(); // Оставайся здесь
  }
*/
  loadConfig();
  watch.begin(); 
  dfPlayer.begin(hwSerial);
  dfPlayer.volume(dfp_volume);
  dfPlayer.setTimeOut(100);
  dfPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  void start_sensors();

  parola.begin();
  catalog[i].speed *= parola.getSpeed()*3;
  catalog[i].pause *= 500;
  parola.setIntensity(yar) ;
  switch(chrift){
      case 0:parola.setFont(_5bite_rus);break;
      case 1:parola.setFont(_5abite_rus);break;
      case 2:parola.setFont(_6bite_rus);break;
     }
  Serial.println("coneft wifi");
  conekt_wifi();
}

// обновлялка строк даты/веремени
void Task1code(void *pvParameters)
{
  for (;;){
    portal.tick();
    ntp.tick();
    if (millis() - tmrW >= 30000 && WiFi.status() != WL_CONNECTED) {
      tmrW = millis();  
      wifiReconect();  
    } else {
      mkTime();
      mkDate();
    }

    nightMode();
    vTaskDelay(500);
  }
}


// говорящие часы или что-то похожее
void Task2code(void *pvParameters)
{
  for (;;)
  {
    switch(modDate){
      case 1:Mod1();break;
      case 2:Mod2();break;
      case 3:displayPogoda1();break;
      case 4:displayPogoda2();break;
      case 5:Mod5();break;
      case 6:displayCurrencyRates();break;
      case 7:Mod7();break;
    }
    if (ntp.minute() == 0 && ntp.second() == 0 && flagGV == true) {
      switch (MG) {
        case 0: Pn = 11;break;
        case 1: Pn = 12;break;
        case 2: Pn = 13;break;
        }
      dfPlayer.volume(dfp_volume);
      dfPlayer.playFolder(Pn, ntp.hour());
    }
    vTaskDelay(10);
  }
}


void Task3code(void *pvParameters)
{
  for (;;)
 {
   if (millis() - tmrN >= 600000 && zapros == true){ tmrN = millis(); printCurrentWeather(); }
   if (millis() - tmrV >= 240000 && zapros == true){ tmrV = millis(); currencyRates(); }
   if (millis() - tmrA >= 120000 && zapros == true){ tmrA = millis(); Anek(); }
   switch(chrift){
      case 0:parola.setFont(_5bite_rus);break;
      case 1:parola.setFont(_5abite_rus);break;
      case 2:parola.setFont(_6bite_rus);break;
     }
   vTaskDelay(1000);
  }
}

void loop(void)
{
   if (parola.displayAnimate())// while (!(parola.displayAnimate()));
  {
    parola.setIntensity(yar) ;
    if(unknown_q>=7)unknown_q=1;
    mkTime();
    if (millis() - tmrM >= sk*2000 && nightModeFlag == false){
      tmrM = millis();
      modDate=unknown_q;
      zapros = false;
      }else{
       zapros = true;
       if (M1 == true || M2 == true || M3 == true || M4 == true || M5 == true) getSens();  
      }
    if (i == ARRAY_SIZE(catalog)){i = 0;y = 0;}  
    if(i == ENA_SPRITE){parola.setSpriteData(sprite[curFX].data, sprite[curFX].width, sprite[curFX].frames,sprite[curFX].data, sprite[curFX].width, sprite[curFX].frames);} 
    parola.displayText(Buf, just, catalog[i].speed, catalog[i].pause, catalog[i].effect, catalog[i].effect);
     Budilok();
     if(i!= 0)y++;
     if(y == 1){i = 0;y = 0;}
     if (millis() - tmrP >= 10000 && nightModeFlag == false){tmrP = millis();i=i+z;z++;} 
     if(z>1){z=0;curFX++;}//28
     if(curFX>15)curFX=0;
     }
  
}

void Mod1()
{
      parola.displayText(dateStringBuff, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
      parola.displayReset();
      unknown_q++;
      modDate=0;
}

void Mod2()
{
    if (M1 == true || M2 == true || M3 == true || M4 == true || M5 == true){
       parola.displayText(home_sens_buff, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
       parola.displayReset();
       unknown_q++;
      modDate=0;
      }else{
      unknown_q++;
      modDate=0;
   }   
}

void Mod5()
{
    if(flagValute == true){
       parola.displayText(BufVal, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
       parola.displayReset();
       unknown_q++;
      modDate=0;
      }else{
      unknown_q++;
      modDate=0;
   }   
}

void displayCurrencyRates()
{
    if(flagValute == true){
       parola.displayText(aforizm_buff, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
       parola.displayReset();
       unknown_q++;
      modDate=0;
      }else{
      unknown_q=unknown_q+2;
      modDate=0;
   }   
}

void Mod7()
{
  if(flagBudilnik == true){
    
    parola.displayText(Buf7, just, sk, 1,PA_NO_EFFECT ,PA_NO_EFFECT);
       parola.displayReset();
     }
}

void mkTime()
{
  textStringBuff1 = ntp.hour();
  if (flagToch == false) {
    if (ntp.second() % 2 == 0)
    {
      textStringBuff1 += ":";
    } else {
      textStringBuff1 += " ";
    }
  } else {
    if (ntp.second() % 2 == 0)
    {
      textStringBuff1 += "$";
    } else {
      textStringBuff1 += "&";
    }
  }
  if (ntp.minute() < 10)textStringBuff1 += "0";
  textStringBuff1 += ntp.minute();
  textStringBuff1.toCharArray(Buf, 20);
}

void mkDate()
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
  Textday.toCharArray(dateStringBuff, 70);
}

void nightMode()
{
  if(someNightModeVar == true){
  if(ntp.hour()== hNon && ntp.minute() == mNon && ntp.second() >= sNon){nightModeFlag = true;yar = 0;flagGV = false; parola.setIntensity(yar);}
  if(ntp.hour()== hNoff && ntp.minute() == mNoff && ntp.second() >= sNoff){nightModeFlag = false;yar = oldyar;flagGV = true; parola.setIntensity(yar);}
  if ((hNon < hNoff) && (ntp.hour() > min(hNon, hNoff) && ntp.hour() < max(hNon, hNoff-1))){nightModeFlag = true;yar = 0;flagGV = false; parola.setIntensity(yar);}
  if ((hNon > hNoff) && (ntp.hour() > max(hNon, hNoff) || ntp.hour() < min(hNon, hNoff-1))){nightModeFlag = true;yar = 0;flagGV = false; parola.setIntensity(yar);}
  if((hNon < hNoff) && (ntp.hour() < min(hNon, hNoff) || ntp.hour() > max(hNon, hNoff+1))){nightModeFlag = false;yar = oldyar;flagGV = true; parola.setIntensity(yar);}
  if((hNon > hNoff) && (ntp.hour() > min(hNon, hNoff) && ntp.hour() < max(hNon, hNoff+1))){nightModeFlag = false;yar = oldyar;flagGV = true; parola.setIntensity(yar);}
    }
}


bool loadConfig() {                                                
  File configFile = LittleFS.open("/config.json", FILE_READ);              
  if(!configFile) {                                               
    if(printCom) Serial.println("Failed to open config file");
    saveConfig();                                                  
    configFile.close();
    return false;                                                  
  }
  size_t size = configFile.size();                                 
  if(size > 20000) {
    if(printCom) Serial.println("Config file size is too large");
    configFile.close();
    return false;                                                  
  }
  jsonConfig = configFile.readString();                            
  DynamicJsonDocument doc(10000);
  deserializeJson(doc, jsonConfig);
  configFile.close();

  wssid = doc["wssid"].as<String>();
  wpass = doc["wpass"].as<String>();
  gorod = doc["gorod"].as<String>();
  latitude = doc["latitude"].as<String>();                     
  longitude = doc["longitude"].as<String>();
  api_key = doc["api_key"].as<String>();
  flagPogoda = doc["flagPogoda"];
  flagValute = doc["flagValute"];
  flagAforizm = doc["flagAforizm"];
  yar = doc["yar"];
  sk = doc["sk"];
  wett = doc["wett"];
  weth = doc["weth"];
  wetp = doc["wetp"];
  CorTemp = doc["CorTemp"];
  corrPress = doc["corrPress"];
  CorHum = doc["CorHum"];
  flagToch = doc["flagToch"];
  oldyar = doc["oldyar"];
  hNon = doc["hNon"];
  mNon = doc["mNon"];
  hNoff = doc["hNoff"];
  mNoff = doc["mNoff"];
  someNightModeVar = doc["someNightModeVar"];
  dfp_volume = doc["Y"];
  MG = doc["MG"];
  swtRTC = doc["swtRTC"];
  printCom = doc["printCom"];
  BUD1 = doc["BUD1"];
  BUD2 = doc["BUD2"];
  BUD3 = doc["BUD3"];
  BUD4 = doc["BUD4"];
  BUD5 = doc["BUD5"];
  BUD6 = doc["BUD6"];
  BUD7 = doc["BUD7"];
  hBud1 = doc["hBud1"];
  mBud1 = doc["mBud1"];
  hBud2 = doc["hBud2"];
  mBud2 = doc["mBud2"];
  hBud3 = doc["hBud3"];
  mBud3 = doc["mBud3"];
  hBud4 = doc["hBud4"];
  mBud4 = doc["mBud4"];
  hBud5 = doc["hBud5"];
  mBud5 = doc["mBud5"];
  hBud6 = doc["hBud6"];
  mBud6 = doc["mBud6"];
  hBud7 = doc["hBud7"];
  mBud7 = doc["mBud7"];
  PaB1 = doc["PaB1"];
  PaB2 = doc["PaB2"];
  PaB3 = doc["PaB3"];
  PaB4 = doc["PaB4"];
  PaB5 = doc["PaB5"];
  PaB6 = doc["PaB6"];
  PaB7 = doc["PaB7"];
  chrift = doc["chrift"];
    
    if(printCom) {
    Serial.print("Load Config : ");
    Serial.println(jsonConfig);
  }
  return true;
}

bool saveConfig() {
  DynamicJsonDocument doc(20000);
  deserializeJson(doc, jsonConfig);

  doc["wssid"] = wssid;
  doc["wpass"] = wpass;
  doc["gorod"] = gorod;
  doc["latitude"] = latitude;                     
  doc["longitude"] = longitude;
  doc["api_key"] = api_key;
  doc["flagPogoda"] = flagPogoda;
  doc["flagValute"] = flagValute;
  doc["flagAforizm"] = flagAforizm;
  doc["yar"] = yar;
  doc["sk"] = sk;
  doc["wett"] = wett;
  doc["weth"] = weth;
  doc["wetp"] = wetp;
  doc["CorTemp"] = CorTemp;
  doc["corrPress"] = corrPress;
  doc["CorHum"] = CorHum;
  doc["flagToch"] = flagToch;
  doc["oldyar"] = oldyar;
  doc["hNon"] = hNon;
  doc["mNon"] = mNon;
  doc["hNoff"] = hNoff;
  doc["mNoff"] = mNoff;
  doc["someNightModeVar"] = someNightModeVar;
  doc["Y"] = dfp_volume;
  doc["MG"] = MG;
  doc["swtRTC"] = swtRTC; 
  doc["printCom"] = printCom;
  doc["BUD1"] = BUD1;
  doc["BUD2"] = BUD2;
  doc["BUD3"] = BUD3;
  doc["BUD4"] = BUD4;
  doc["BUD5"] = BUD5;
  doc["BUD6"] = BUD6;
  doc["BUD7"] = BUD7;
  doc["hBud1"] = hBud1;
  doc["mBud1"] = mBud1;
  doc["hBud2"] = hBud2;
  doc["mBud2"] = mBud2;
  doc["hBud3"] = hBud3;
  doc["mBud3"] = mBud3;
  doc["hBud4"] = hBud4;
  doc["mBud4"] = mBud4;
  doc["hBud5"] = hBud5;
  doc["mBud5"] = mBud5;
  doc["hBud6"] = hBud6;
  doc["mBud6"] = mBud6;
  doc["hBud7"] = hBud7;
  doc["mBud7"] = mBud7;
  doc["PaB1"] = PaB1;
  doc["PaB2"] = PaB2;
  doc["PaB3"] = PaB3;
  doc["PaB4"] = PaB4;
  doc["PaB5"] = PaB5;
  doc["PaB6"] = PaB6;
  doc["PaB7"] = PaB7;
  doc["chrift"] = chrift;
  
    jsonConfig = "";
     if(serializeJson(doc, jsonConfig)==0){
    Serial.println(F("Failed to write to jsonConfig"));
  }  
  File configFile = LittleFS.open("/config.json", FILE_WRITE);               
  if(!configFile) {
    configFile.close();
    return false;
  }
  if(serializeJson(doc, configFile)==0){
    Serial.println(F("Failed to write to file"));
  } 
  if(printCom) {
    Serial.print("Save Config : ");
    Serial.println(jsonConfig);
  }
  configFile.close();
  return true;
}

//будильник
bool BUD,BUD1,BUD2,BUD3,BUD4,BUD5,BUD6,BUD7;
int hBud,hBud1,hBud2,hBud3,hBud4,hBud5,hBud6,hBud7;
int mBud,mBud1,mBud2,mBud3,mBud4,mBud5,mBud6,mBud7;
bool flagBudilnik = false;
int Pap,PaB1,PaB2,PaB3,PaB4,PaB5,PaB6,PaB7;


void Budilok()
{
  switch(ntp.dayWeek()){
    case 1:if(BUD1==true){hBud=hBud1;mBud=mBud1;Pap=PaB1;BUD = true;
    }else{
     BUD = false; 
    }
    break;
    case 2:if(BUD2==true){hBud=hBud2;mBud=mBud2;Pap=PaB2;BUD = true;
    }else{
     BUD = false; 
    }
    break;
    case 3:if(BUD3==true){hBud=hBud3;mBud=mBud3;Pap=PaB3;BUD = true;
    }else{
     BUD = false; 
    }
    break;
    case 4:if(BUD4==true){hBud=hBud4;mBud=mBud4;Pap=PaB4;BUD = true;
    }else{
     BUD = false; 
    }
    break;
    case 5:if(BUD5==true){hBud=hBud5;mBud=mBud5;Pap=PaB5;BUD = true;
    }else{
     BUD = false; 
    }
    break;
    case 6:if(BUD6==true){hBud=hBud6;mBud=mBud6;Pap=PaB6;BUD = true;
    }else{
     BUD = false; 
    }
    break;
    case 7:if(BUD7==true){hBud=hBud7;mBud=mBud7;Pap=PaB7;BUD = true;
    }else{
     BUD = false; 
    }
    break;
  }
  if(hBud == ntp.hour() && mBud == ntp.minute() && ntp.second() == 00 && BUD == true){
      flagBudilnik = true;
      dfPlayer.volume(dfp_volume);
      dfPlayer.playFolder(14, Pap);
      Mod7();
      }else{
       flagBudilnik = false; 
      }
}
