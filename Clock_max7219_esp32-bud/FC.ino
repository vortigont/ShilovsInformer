bool loadConfig() {                                                
  File configFile = SPIFFS.open("/config.json", FILE_READ);              
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
  DynamicJsonDocument doc(20000);                                    
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
  MNR = doc["MNR"];
  Y = doc["Y"];
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
//=================================================================
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
  doc["MNR"] = MNR;
  doc["Y"] = Y;
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
  File configFile = SPIFFS.open("/config.json", FILE_WRITE);               
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
