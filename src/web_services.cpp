#include "main.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


//Афоризм
String aforizm;
String location_anek;
String location_awt;

bool flagAforizm = false;

float usd;
float eur;
float byn;
float uah;

void getAfof();

void Anek() {
  location_anek.clear();
  location_awt.clear();
      
  String line;
  line.reserve(1000);
  if(WiFi.status() == WL_CONNECTED){
   //kateganekd();
   HTTPClient http;
  String apiGetData = "http://api.forismatic.com/api/1.0/?method=getQuote&key=457653&format=json&lang=ru";//mySrce
  Serial.println("Getting News Data");
  Serial.println(apiGetData);
  http.begin(apiGetData);
  int httpCode = http.GET();
    if (httpCode > 0) {
      if(printCom) Serial.printf("    [HTTP] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        line = http.getString();
      } else {
        Serial.println("connection for news data failed: "); //error message if no client connect
        Serial.println();
        return;
      }
    }
    http.end();
  }

    if (printCom)Serial.println("line =" + line);
    const size_t capacity = 2384; //https://arduinojson.org/v6/assistant/
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, line);
   //JsonObject anek = doc[0];
   const char*anekdot = doc["quoteText"];
    location_anek = anekdot;
    const char*awtor = doc["quoteAuthor"];
    location_awt = awtor;
    getAfof();

   if (printCom) {
   Serial.print("АФОРИЗМЫ: ");
   Serial.println(location_anek);
   Serial.print("ААВТОР: ");
   Serial.println(location_awt);
   }
}

void repl()
{
 aforizm.replace("»", ">");
 aforizm.replace("«", "<");
 aforizm.replace("—", "-");

}

void getCurrencyRates()
{  
    String valutedok ("     1 доллар = ");
     valutedok += String(usd, 2);
     valutedok += " рублей. ";
     valutedok += "1 евро = ";
     valutedok += String(eur, 2);
     valutedok += " рублей. ";
     valutedok += "1 беллоруский рубль = ";
     valutedok += String(byn, 2);
     valutedok += " рублей. ";
     valutedok.toCharArray(BufVal, 250);      
}

void currencyRates() { 
 String line = "";
   if(WiFi.status() == WL_CONNECTED){
  HTTPClient http;
   String serverPath = "https://www.cbr-xml-daily.ru/daily_json.js?date_req=" + String(ntp.day()) + "." + months[ntp.month()] + "." + String(ntp.year());
  Serial.println("Getting valute");
   http.begin(serverPath);
   int httpCode = http.GET();
   if (httpCode > 0) {
      Serial.printf("    [HTTP] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        line = http.getString();
      }else{
    Serial.println("connection for news data failed: " + String(serverPath)); //error message if no client connect
    Serial.println();
    return;
      } 
    }
    http.end();
   }
  
    const size_t capacity = JSON_ARRAY_SIZE(6) + JSON_OBJECT_SIZE(30) + 6128; //https://arduinojson.org/v6/assistant/
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, line);
    
     float ud  = doc["Valute"]["USD"]["Value"];
     usd = ud;
     float er  = doc["Valute"]["EUR"]["Value"];
     eur = er;
     float bn  = doc["Valute"]["BYN"]["Value"];
     byn = bn;
     float uh = doc["Valute"]["UAH"]["Value"];
     uah = uh;
     getCurrencyRates();
     if (printCom) {
     Serial.println("1 доллар = " + String(usd) + " рублей.");
     Serial.println("1 евро = " + String(eur) + " рублей.");
     Serial.println("1 беллоруский рубль = " + String(byn) + " рублей.");
    }
}

void getAfof()
{  
     aforizm = "      ";
     aforizm += "Афоризм : ";
     aforizm += location_anek;
     if(location_awt != 0){
     aforizm += " Автор : ";
     aforizm += location_awt;
     repl();
     }
    aforizm.toCharArray(aforizm_buff, 500);
}
