//===============================================================================================================================//
//                              ПОГОДА                                                //
//===============================================================================================================================//
#include "main.h"
#include <UnixTime.h>
#include <OpenWeather.h>
#define TIME_OFFSET 1UL+10800

String gorod ="Гомеле", latitude = "52.43", longitude = "30.97", api_key = "your_key";
String units = "metric";  // or "imperial"
String language = "ru";   // See notes tab

OW_Weather ow;

int timezone = 3;
int deg;
float hum,windspeed,pres;
//int location_code;
float Tmper,temper,temp_min1,temp_min2,temp_min3,temp_min4,temp_min5,temp_max1,temp_max2,temp_max3,temp_max4,temp_max5;
//int daily_code1 ,daily_code2 ,daily_code3 ,daily_code4 ,daily_code5;
String daily_dis1 ,daily_dis2 ,daily_dis3 ,daily_dis4 ,daily_dis5;
int dates1,dates2,dates3,dates4,dates5;
UnixTime stamp(3);
int di = 0;
int d, d1,d2,d3,d4,d5;
String voshod,zakat,newvosh,Timeper,vosh,zakt,descript,degString;
String pogodaS;
String pogodaP; 
String POGODA;

int vos1,vos2,zak1,zak2;

//погода
bool flagPogoda = false;

char Buf2[300];
char Buf4[250];
char Buf3[] = "     Нет погоды";
char Buf5[] = "     Нет прогноза погоды";

/***************************************************************************************
**                          Convert unix time to a time string
***************************************************************************************/
String strTime(time_t unixTime){
  unixTime += TIME_OFFSET;
  return ctime(&unixTime);
}

void printCurrentWeather()
{

  OW_current *current = new OW_current;
  OW_hourly *hourly = new OW_hourly;
  OW_daily  *daily = new OW_daily;

  Serial.println("\nRequesting weather information from OpenWeather... ");

  ow.getForecast(current, hourly, daily, api_key, latitude, longitude, units, language);
  Serial.println("");
  Serial.println("Weather from Open Weather\n");

  // Position as reported by Open Weather
  Serial.print("Latitude            : "); Serial.println(ow.lat);
  Serial.print("Longitude           : "); Serial.println(ow.lon);
  // We can use the timezone to set the offset eventually...
  Serial.print("Timezone            : "); Serial.println(ow.timezone);
  Serial.println();
  // if(parseOK == true){
       // flagzapros = true;
     // }else{
      //  flagzapros = false;
     // }
  if (current)
  {
    di = 0;
    Serial.println("############### Current weather ###############\n");
    Serial.print("dt (time)        : "); Serial.println(strTime(current->dt));
    Serial.print("sunrise          : "); Serial.println(strTime(current->sunrise));
    Serial.print("sunset           : "); Serial.println(strTime(current->sunset));
    Serial.print("temp             : "); Serial.println(current->temp);
    //Serial.print("feels_like       : "); Serial.println(current->feels_like);
    Serial.print("pressure         : "); Serial.println(current->pressure);
    Serial.print("humidity         : "); Serial.println(current->humidity);
    //Serial.print("dew_point        : "); Serial.println(current->dew_point);
    //Serial.print("uvi              : "); Serial.println(current->uvi);
    Serial.print("clouds           : "); Serial.println(current->clouds);
    //Serial.print("visibility       : "); Serial.println(current->visibility);
    Serial.print("wind_speed       : "); Serial.println(current->wind_speed);
    //Serial.print("wind_gust        : "); Serial.println(current->wind_gust);
    Serial.print("wind_deg         : "); Serial.println(current->wind_deg);
    //Serial.print("rain             : "); Serial.println(current->rain);
    //Serial.print("snow             : "); Serial.println(current->snow);
    //Serial.println();
    Serial.print("id               : "); Serial.println(current->id);
    //if(location_code == 0){
    //flagzapros = false;
     //}else{
    //flagzapros = true;
    // }
     Serial.print("Запрос - ");
     Serial.println(flagzapros); 
    //Serial.print("main             : "); Serial.println(current->main);
    Serial.print("description      : "); Serial.println(current->description);
    //Serial.print("icon             : "); Serial.println(current->icon);
    temper = current->temp;
    location_code = current->id;
    deg = current->wind_deg;
    windspeed = current->wind_speed;
    hum = current->humidity;
    descript = current->description;
    pres = current->pressure/1.355269;
    
    Serial.println();
  }

 // if (hourly)
 // {
    //Serial.println("############### Hourly weather  ###############\n");
   // for (int i = 0; i < MAX_HOURS; i++)
   // {
    
   // }
 // }

  if (daily)
  {
    Serial.println("###############  Daily weather  ###############\n");
    for (di = 0; di < MAX_DAYS; di++)
    {
      Serial.print("Daily summary   "); if (di < 10) Serial.print(" "); Serial.print(di);
      Serial.println();
      Serial.print("dt (time)        : "); Serial.println(strTime(daily->dt[di]));
      Serial.print("sunrise          : "); Serial.println(strTime(daily->sunrise[di]));
      Serial.print("sunset           : "); Serial.println(strTime(daily->sunset[di]));
      Serial.print("temp.min         : "); Serial.println(daily->temp_min[di]);
      Serial.print("temp.max         : "); Serial.println(daily->temp_max[di]);
      Serial.println();
      Serial.print("id               : "); Serial.println(daily->id[di]);
      //Serial.print("main             : "); Serial.println(daily->main[di]);
      Serial.print("description      : "); Serial.println(daily->description[di]);
      //Serial.print("icon             : "); Serial.println(daily->icon[di]);
      //Serial.print("pop              : "); Serial.println(daily->pop[di]);
       switch(di){
       case 0:temp_min1 = daily->temp_min[di];temp_max1 = daily->temp_max[di];daily_dis1 = daily->description[di];dates1 = daily->dt[di];break; 
       case 1:temp_min2 = daily->temp_min[di];temp_max2 = daily->temp_max[di];daily_dis2 = daily->description[di];dates2 = daily->dt[di];break;
       case 2:temp_min3 = daily->temp_min[di];temp_max3 = daily->temp_max[di];daily_dis3 = daily->description[di];dates3 = daily->dt[di];break;
       case 3:temp_min4 = daily->temp_min[di];temp_max4 = daily->temp_max[di];daily_dis4 = daily->description[di];dates4 = daily->dt[di];break;
       case 4:temp_min5 = daily->temp_min[di];temp_max5 = daily->temp_max[di];daily_dis5 = daily->description[di];dates5 = daily->dt[di];break;
      }
       
       stamp.getDateTime(dates1); Serial.print("ДАТА : "); Serial.println(stamp.day);d1 = stamp.day;
       stamp.getDateTime(dates2); Serial.print("ДАТА : "); Serial.println(stamp.day);d2 = stamp.day;
       stamp.getDateTime(dates3); Serial.print("ДАТА : "); Serial.println(stamp.day);d3 = stamp.day;
       stamp.getDateTime(dates4); Serial.print("ДАТА : "); Serial.println(stamp.day);d4 = stamp.day;
       stamp.getDateTime(dates5); Serial.print("ДАТА : "); Serial.println(stamp.day);d5 = stamp.day;
       voshod = strTime(daily->sunrise[0]);
       zakat = strTime(daily->sunset[0]);
       if(d<10){
        vos1 = 11;zak1 = 11;vos2 = 16;zak2 = 16;
        }else{
        vos1 = 11;zak1 = 11;vos2 = 16;zak2 = 16 ;
       }
       vosh = voshod.substring(vos1,vos2);//vos1,vos2
       zakt = zakat.substring(zak1,zak2);//zak1,zak2
       Serial.println(vosh);
       Serial.println(zakt);
       Serial.println(ow.timezone);
      // Serial.println(strTime(daily->sunset[0]));
       Serial.println();
    }
  }
   // Delete to free up space and prevent fragmentation as strings change in length
  delete current;
  delete hourly;
  delete daily;
   if (deg >= 345 || deg <= 22)  degString = "Северный";
   if (deg >= 23  && deg <= 68)  degString = "Северо-Восточный";
   if (deg >= 69  && deg <= 114) degString = "Восточный";
   if (deg >= 115 && deg <= 160) degString = "Юго-Восточный";
   if (deg >= 161 && deg <= 206) degString = "Южный";
   if (deg >= 207 && deg <= 252) degString = "Юго-Западный";
   if (deg >= 253 && deg <= 298) degString = "Западный";
   if (deg >= 299 && deg <= 344) degString = "Северо-Западный";
   pogodaS = " ";
   if(temper>0){
   pogodaS += "      Сейчас в " + String(gorod) + ":" + " Температура " + "+" + String(temper, 1) + "*" + "C";
   }else{
   pogodaS += "      Сейчас в " + String(gorod) + ":" + " Температура " + String(temper, 1) + "*" + "C"; 
   }
   pogodaS += " Влажность " + String(hum,0) + "% ";
   pogodaS += " Давление " + String(pres,0) + "ммРс ";
   pogodaS += " Ветер " + degString + " "+ String(windspeed, 1) + "м/с ";
   pogodaS += descript;
   pogodaS += " Восход в " + vosh + " "+ "Закат в " + zakt;
//====================прогноз====================================================================================
   pogodaP = " ";
   pogodaP += "    Завтра температура от ";
   if(temp_min2>0){
    pogodaP += "+" + String(temp_min2,1) + "*" + "C" + " до ";
   }else{
   pogodaP += String(temp_min2,1) + "*" + "C" + " до ";
   }
   if(temp_max2>0){
   pogodaP += "+" + String(temp_max2,1) + "*" + "C "; 
   }else{
   pogodaP += String(temp_max2,1) + "*" + "C ";
   }
   pogodaP += daily_dis2;
   pogodaP += "   Послезавтра температура от ";
   if(temp_min3>0){
   pogodaP += "+" + String(temp_min3,1) + "*" + "C" + " до "; 
   }else{
   pogodaP += String(temp_min3,1) + "*" + "C" + " до ";
   }
   if(temp_max3>0){
   pogodaP += "+" + String(temp_max3,1) + "*" + "C "; 
   }else{
   pogodaP += String(temp_max3,1) + "*" + "C ";
   }
   pogodaP += daily_dis3;
   POGODA = pogodaS + pogodaP;
   pogodaS.toCharArray(Buf2, 300);
   pogodaP.toCharArray(Buf4, 250);
   
   if(current->id == 0){
    flagzapros = false;
     }else{
    flagzapros = true;
     }
 
}

void displayPogoda1()
{
  if(flagPogoda == true){
     if(location_code != 0){
         parola.displayText(Buf2, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
         }else{
         parola.displayText(Buf3, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
         }
      unknown_q++;
      modDate=0;
   }else{
      unknown_q++;
      modDate=0;
   }
  
}

void displayPogoda2()
{
    if(flagPogoda == true){
     if(location_code != 0){
         parola.displayText(Buf4, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
         }else{
         parola.displayText(Buf5, just, sk, 1,PA_SCROLL_LEFT ,PA_SCROLL_LEFT );
         }
      unknown_q++;
      modDate=0;
     }else{
      unknown_q++;
      modDate=0;
   }   
  
}
