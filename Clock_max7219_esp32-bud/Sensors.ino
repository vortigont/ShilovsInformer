
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
     Domtemhumpres = "    ";
     Domtemhumpres += "В помещении";
     if (wett == 1 || wett == 2 || wett == 3 || wett == 4 || wett == 5)Domtemhumpres += ", температура: +";
     if (wett == 1){getsensorsBme();Domtemhumpres += String(tempBme + CorTemp, 0);}
     if (wett == 2){getsensorsAth();sensors_event_t temp;aht_temp->getEvent(&temp);Domtemhumpres += String(temp.temperature + CorTemp, 0);}
     if (wett == 3){sensorsBmp280();Domtemhumpres += String(tempBmp + CorTemp, 0);}
     if (wett == 4){sensorsBmp180();Domtemhumpres += String(tempBmp + CorTemp, 0);}
     if (wett == 5){getsensGY21();Domtemhumpres += String(htu.getTemperature() + CorTemp, 0);}
     if (wett == 1 || wett == 2 || wett == 3 || wett == 4 || wett == 5)Domtemhumpres += "*C";
     if (weth == 1 || weth == 2 || weth == 3 || weth == 4)Domtemhumpres += " влажность: ";
     if (weth == 1)Domtemhumpres += String(humBme + CorHum, 0);
     if (weth == 2) {getsensorsAth();sensors_event_t humidity;aht_humidity->getEvent(&humidity);Domtemhumpres += String(humidity.relative_humidity + CorHum, 0);}
     if (weth == 3)Domtemhumpres += String(hum,0);
     if (weth == 4){getsensGY21();Domtemhumpres += String(htu.getHumidity(), 0);}
     if (weth == 1 || weth == 2 || weth == 3 || weth == 4)Domtemhumpres += "%";
     if (wetp == 1 || wetp == 2 || wetp == 3 || wetp == 4)Domtemhumpres += ", давление: " ;
     if (wetp == 1){getsensorsBme();Domtemhumpres += String(pressBme + corrPress, 0);}
     if (wetp == 2)Domtemhumpres += String(pres,0);
     if (wetp == 3){sensorsBmp280();Domtemhumpres += String(pressBmp + corrPress, 0);}
     if (wetp == 4){sensorsBmp180();Domtemhumpres += String(pressBmp + corrPress, 0);}
     if (wetp == 1 || wetp == 2 || wetp == 3 || wetp == 4)Domtemhumpres += " ммРс";
      Domtemhumpres.toCharArray(Bufthp, 250);
}
