void Portal()
{
  portal.tick();
   if (portal.form("/update")) {
    loadConfig();
    gorod = portal.getString("txt");
    latitude = portal.getString("txt1");
    longitude = portal.getString("txt2");
    api_key = portal.getString("txt3");
    printCurrentWeather();
     saveConfig();
   }
     if (portal.click()) {
    loadConfig();
    if (portal.click("selchrift")){chrift = portal.getSelected("selchrift", "ТОНКИЙ,ТОНКИЙ-ВЫСОКИЙ,ТОЛСТЫЙ");}
    if (portal.click("swflagPogoda")){flagPogoda = portal.getCheck("swflagPogoda");}
    if (portal.click("swvalu")){flagValute = portal.getCheck("swvalu");if(flagValute==true)Val(); }
    if (portal.click("swchut")){flagAforizm = portal.getCheck("swchut");if(flagAforizm==true);Anek(); }
    if (portal.click("sldyar")){yar = portal.getInt("sldyar");oldyar=yar;P.setIntensity(yar);}
    if (portal.click("sldq")){sk = portal.getInt("sldq");}
    if (portal.click("selt")){wett = portal.getSelected("selt", "NO,  BME280, AHTxx, BMP280, BMP180, GY21");}
    if (portal.click("selh")){weth = portal.getSelected("selh", "NO,  BME280, AHTxx, WM, GY21");}
    if (portal.click("selp")){wetp = portal.getSelected("selp", "NO,  BME280, WM, BMP280, BMP180");}
    if (portal.click("sldct")){CorTemp = portal.getInt("sldct");}
    if (portal.click("sldch")){CorHum = portal.getInt("sldch");}
    if (portal.click("sldcp")){corrPress = portal.getInt("sldcp");}
    if (portal.click("swflagToch")){flagToch = portal.getCheck("swflagToch");Time();}
    if (portal.click("swBUD1")){BUD1 = portal.getCheck("swBUD1");}
    if (portal.click("swBUD2")){BUD2 = portal.getCheck("swBUD2");}
    if (portal.click("swBUD3")){BUD3 = portal.getCheck("swBUD3");}
    if (portal.click("swBUD4")){BUD4 = portal.getCheck("swBUD4");}
    if (portal.click("swBUD5")){BUD5 = portal.getCheck("swBUD5");}
    if (portal.click("swBUD6")){BUD6 = portal.getCheck("swBUD6");}
    if (portal.click("swBUD7")){BUD7 = portal.getCheck("swBUD7");}
    if (portal.click("selhBud1")){hBud1 = portal.getSelected("selhBud1", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23");}
    if (portal.click("selmBud1")){mBud1 = portal.getSelected("selmBud1", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59");}
    if (portal.click("selhBud2")){hBud2 = portal.getSelected("selhBud2", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23");}
    if (portal.click("selmBud2")){mBud2 = portal.getSelected("selmBud2", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59");}
    if (portal.click("selhBud3")){hBud3 = portal.getSelected("selhBud3", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23");}
    if (portal.click("selmBud3")){mBud3 = portal.getSelected("selmBud3", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59");}
    if (portal.click("selhBud4")){hBud4 = portal.getSelected("selhBud4", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23");}
    if (portal.click("selmBud4")){mBud4 = portal.getSelected("selmBud4", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59");}
    if (portal.click("selhBud5")){hBud5 = portal.getSelected("selhBud5", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23");}
    if (portal.click("selmBud5")){mBud5 = portal.getSelected("selmBud5", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59");}
    if (portal.click("selhBud6")){hBud6 = portal.getSelected("selhBud6", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23");}
    if (portal.click("selmBud6")){mBud6 = portal.getSelected("selmBud6", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59");}
    if (portal.click("selhBud7")){hBud7 = portal.getSelected("selhBud7", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23");}
    if (portal.click("selmBud7")){mBud7 = portal.getSelected("selmBud7", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59");}
    if (portal.click("selPaB1")){PaB1 = portal.getSelected("selPaB1", "NO, 1,  2, 3, 4, 5");}
    if (portal.click("selPaB2")){PaB2 = portal.getSelected("selPaB2", "NO, 1,  2, 3, 4, 5");}
    if (portal.click("selPaB3")){PaB3 = portal.getSelected("selPaB3", "NO, 1,  2, 3, 4, 5");}
    if (portal.click("selPaB4")){PaB4 = portal.getSelected("selPaB4", "NO, 1,  2, 3, 4, 5");}
    if (portal.click("selPaB5")){PaB5 = portal.getSelected("selPaB5", "NO, 1,  2, 3, 4, 5");}
    if (portal.click("selPaB6")){PaB6 = portal.getSelected("selPaB6", "NO, 1,  2, 3, 4, 5");}
    if (portal.click("selPaB7")){PaB7 = portal.getSelected("selPaB7", "NO, 1,  2, 3, 4, 5");}
    if (portal.click("selMG")){
      MG = portal.getSelected("selMG", "ЖЕНСКИЙ,МУЖСКОЙ,КУРАНТЫ");
      switch (MG) {
        case 0: Pn = 11; break;
        case 1: Pn = 12; break;
        case 2: Pn = 13; break;
      }
      dfPlayer.setTimeOut(2000);
      dfPlayer.playFolder(Pn, 35);
     }
    if (portal.click("sldY")){Y = portal.getInt("sldY");dfPlayer.volume(Y);}
    if (portal.click("btnrst"))ESP.restart();
    if (portal.click("swswtRTC")){swtRTC = portal.getCheck("swswtRTC");watch.settime(ntp.second(),ntp.minute(),ntp.hour(),ntp.day(),ntp.month(),ntp.year(),ntp.dayWeek()); }
    if (portal.click("swcom")){printCom = portal.getCheck("swcom");}   
    if (portal.click("swMNR")){MNR = portal.getCheck("swMNR");}
    if (portal.click("selhNon")){hNon = portal.getSelected("selhNon", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23");}
    if (portal.click("selmNon")){mNon = portal.getSelected("selmNon", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59");}
    if (portal.click("selhNoff")){hNoff = portal.getSelected("selhNoff", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23");}
    if (portal.click("selmNoff")){mNoff = portal.getSelected("selmNoff", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59");}

  }
  saveConfig();
}
