#include <array>
#include "main.h"
#include <Adafruit_BMP280.h>
#include <Adafruit_BMP085.h>
#include "Adafruit_BME280.h"
#include <Adafruit_AHTX0.h>
#include <GyverHTU21D.h>
#include "pogoda.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
Adafruit_BMP280 bmp;
Adafruit_BMP085 bmp180;
GyverHTU21D htu;
Adafruit_AHTX0 aht;
Adafruit_Sensor *aht_humidity, *aht_temp;
iarduino_RTC watch(RTC_DS3231);


//датчики
bool M1, M2, M3, M4, M5;
int wett, wetp, weth;
int humath;

float tempBme = 0;
float humBme = 0;
float pressBme = 0;
float altBme = 0;
//RTC
bool swtRTC = false;
bool flagRTC = false;

bool pressSys = 1;
float tempGY = 0;
float humGY = 0;
float humAT = 0;
float tempAT = 0;
float tempBmp = 0;
float pressBmp = 0;
float altBmp = 0;
bool bmp280 = false;
bool BMP180 = false;

String room_temhumpres_string;
int CorTemp = 0;// коррекция температуры
int  corrPress = 0;// коррекция давления
int CorHum = 0;// коррекция влажности

//--------------------------------------------------------------------------
void getsensorsBme() {
  // if (bme280 == false) return;
  tempBme = bme.readTemperature();
  humBme = bme.readHumidity();
  pressBme = bme.readPressure()  / (pressSys == 1 ? 1.3332239 : 1);
  pressBme = (int) pressBme / 100;

  altBme = bme.readAltitude(SEALEVELPRESSURE_HPA);   //bme.readAltitudeMeter()  bme.readAltitudeFeet()
  if (printCom) {
      Serial.println("Temperature BME280: " + String(tempBme) + " *C,  Humidity: " + String(humBme) + " %,  Pressure: " + String(int(pressBme)) + " мм рт.ст." + ",  Approx altitude: " + String(altBme) + " m");
  }
}
//--------------------------------------------------------------------------

void sensorsBmp280() {
  if (bmp280 == true) {
    tempBmp = bmp.readTemperature();
    pressBmp = bmp.readPressure() * 0.00750063755419211;
    pressBmp = (int) pressBmp;
    altBmp = bmp.readAltitude(1013.25);
    if (printCom) {
      if (bmp280 == true) Serial.println("Temperature BMP280: " + String(tempBmp) + " *C,  Pressure: " + String(pressBmp) + " mmHg,  Approx altitude: " + String(altBmp) + " m");
    }
  }
}
void sensorsBmp180(){
  if (BMP180 == true) {
    tempBmp = bmp180.readTemperature();
    pressBmp = bmp180.readPressure() * 0.00750063755419211;
    pressBmp = (int) pressBmp;
    altBmp = bmp180.readAltitude(101500);
    if (printCom) {
      if (BMP180 == true) Serial.println("Temperature BMP180: " + String(tempBmp) + " *C,  Pressure: " + String(pressBmp) + " mmHg,  Approx altitude: " + String(altBmp) + " m");
    }
  }
}
//--------------------------------------------------------------------------
void getsensorsAth() {
    
  sensors_event_t humidity;// sensors_event_t humidity1;
  sensors_event_t temp;//sensors_event_t temp1;
  aht_humidity->getEvent(&humidity);//aht_humidity->getEvent(&humidity1);
  aht_temp->getEvent(&temp);//aht_temp->getEvent(&temp1);
  temp.temperature = temp.temperature;
  humidity.relative_humidity = humidity.relative_humidity;
  if(printCom){
  Serial.print("Температура: "); Serial.print(temp.temperature, 0); Serial.println("C");
  Serial.print("Влажность: "); Serial.print(humidity.relative_humidity, 0); Serial.println("%");
  }
  humath = humidity.relative_humidity, 0;
}
//---------------------------------------------------------------------------------------------
void getsensGY21()
{
  htu.requestTemperature();                 // Запрашиваем преобразование
  delay(100);                               // Ждем окончания (см. доку)
  if (htu.readTemperature()) { 
    if(printCom){                            // Читаем температуру из датчика и проверяем
    Serial.print("Temp: ");
    Serial.print(htu.getTemperature());     // В случае успеха выводим температуру в порт
    Serial.println(" *C");
    }
  }

  // Читаем влажность
  htu.requestHumidity();                    // Запрашиваем преобразование
  delay(100);                               // Ждем окончания (см. доку)
  if (htu.readHumidity()) {                 // Читаем влажность из датчика и проверяем
    if(printCom){
    Serial.print("Hum: ");
    Serial.print(htu.getHumidity());        // В случае успеха выводим влажность в порт
    Serial.println(" %");
    }
  }
}

void getSens()
{
     room_temhumpres_string = "    ";
     room_temhumpres_string += "В помещении";
     if (wett == 1 || wett == 2 || wett == 3 || wett == 4 || wett == 5)room_temhumpres_string += ", температура: +";
     if (wett == 1){getsensorsBme();room_temhumpres_string += String(tempBme + CorTemp, 0);}
     if (wett == 2){getsensorsAth();sensors_event_t temp;aht_temp->getEvent(&temp);room_temhumpres_string += String(temp.temperature + CorTemp, 0);}
     if (wett == 3){sensorsBmp280();room_temhumpres_string += String(tempBmp + CorTemp, 0);}
     if (wett == 4){sensorsBmp180();room_temhumpres_string += String(tempBmp + CorTemp, 0);}
     if (wett == 5){getsensGY21();room_temhumpres_string += String(htu.getTemperature() + CorTemp, 0);}
     if (wett == 1 || wett == 2 || wett == 3 || wett == 4 || wett == 5)room_temhumpres_string += "*C";
     if (weth == 1 || weth == 2 || weth == 3 || weth == 4)room_temhumpres_string += " влажность: ";
     if (weth == 1)room_temhumpres_string += String(humBme + CorHum, 0);
     if (weth == 2) {getsensorsAth();sensors_event_t humidity;aht_humidity->getEvent(&humidity);room_temhumpres_string += String(humidity.relative_humidity + CorHum, 0);}
     if (weth == 3)room_temhumpres_string += String(hum,0);
     if (weth == 4){getsensGY21();room_temhumpres_string += String(htu.getHumidity(), 0);}
     if (weth == 1 || weth == 2 || weth == 3 || weth == 4)room_temhumpres_string += "%";
     if (wetp == 1 || wetp == 2 || wetp == 3 || wetp == 4)room_temhumpres_string += ", давление: " ;
     if (wetp == 1){getsensorsBme();room_temhumpres_string += String(pressBme + corrPress, 0);}
     if (wetp == 2)room_temhumpres_string += String(pres,0);
     if (wetp == 3){sensorsBmp280();room_temhumpres_string += String(pressBmp + corrPress, 0);}
     if (wetp == 4){sensorsBmp180();room_temhumpres_string += String(pressBmp + corrPress, 0);}
     if (wetp == 1 || wetp == 2 || wetp == 3 || wetp == 4)room_temhumpres_string += " ммРс";
      room_temhumpres_string.toCharArray(home_sens_buff, 250);
}

void DateRTC()
{
  String Textrtcday("       ");
  Textrtcday += watch.day;
  Textrtcday += " ";
  Textrtcday += months[watch.month];
  Textrtcday += " ";
  Textrtcday += watch.year;
  Textrtcday += " ";
  Textrtcday += "года";
  Textrtcday += " ";
  Textrtcday += weekDay[watch.weekday];
  Textrtcday.toCharArray(dateStringBuff, 70);
  
}

void TimeRTC()
{
  String textrtc1(watch.Hours);
  
  if (watch.seconds % 2 == 0)
    {
    textStringBuff1 += "'";
    } else {
    textStringBuff1 += "<";
    }
  if (watch.minutes < 10)textrtc1 += "0";
  textrtc1 += watch.minutes;
  textrtc1.toCharArray(Buf, 20);
}

void wifiReconect()
{
     if(printCom) Serial.println("no wifi");
      WiFi.mode(WIFI_STA);
      WiFi.disconnect(true);
      WiFi.begin();
      if(swtRTC == true){
      flagRTC = true;
      DateRTC();
      TimeRTC();
    }
}


void start_sensors(){
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
  } else if (printCom)
      Serial.println("Did not find BMP180 sensor!");

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
}
