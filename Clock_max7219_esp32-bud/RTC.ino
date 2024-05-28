void Conekted()
{
     if(printCom)Serial.println("no wifi");
      WiFi.mode(WIFI_STA);
      WiFi.disconnect(true);
      WiFi.begin();
      if(swtRTC == true){
      flagRTC = true;
      DateRTC();
      TimeRTC();
    }
}

void DateRTC()
{
  String Textrtcday="";
  Textrtcday = "";
  Textrtcday += "       ";
  Textrtcday += watch.day;
  Textrtcday += " ";
  Textrtcday += months[watch.month];
  Textrtcday += " ";
  Textrtcday += watch.year;
  Textrtcday += " ";
  Textrtcday += "года";
  Textrtcday += " ";
  Textrtcday += weekDay[watch.weekday];
  Textrtcday.toCharArray(Buf1, 70);
  
}
void TimeRTC()
{
  String textrtc1="";
  textrtc1 = "";
  textrtc1 += watch.Hours;
  
  if (watch.seconds % 2 == 0)
    {
    text1 += "'";
    } else {
    text1 += "<";
    }
  if (watch.minutes < 10)textrtc1 += "0";
  textrtc1 += watch.minutes;
  textrtc1.toCharArray(Buf, 20);
}
