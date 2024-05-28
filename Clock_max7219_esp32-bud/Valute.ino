void Val() { 
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
   }
  http.end();
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
     getVal();
     if (printCom) {
     Serial.println("1 доллар = " + String(usd) + " рублей.");
     Serial.println("1 евро = " + String(eur) + " рублей.");
     Serial.println("1 беллоруский рубль = " + String(byn) + " рублей.");
    }
}
void getVal()
{  
     valutedok = " ";
     valutedok += "     1 доллар = ";
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
