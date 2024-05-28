void build() {
  String s;
  BUILD_BEGIN(s);
  GP.THEME(GP_DARK);
  GP.TITLE("🔴🟢🔵 𝕮𝖑𝖔𝖈𝖐", "font30 fontcyan_000000");
  if (portal.uri() == "/update") {
    GP.HR();
    GP.LABEL("ПОГОДА", "font20 fontcyan_16747a"); GP.BREAK();
    GP.HR();
    GP.LABEL("ВАШИ КООРДИНАТЫ", "font16 fontred_a5381b"); GP.BREAK();
    GP.LABEL("И ВАШ API С ПОГОДНОГО СЕРВЕРА", "font16 fontred_a5381b"); GP.BREAK();
    GP.FORM_BEGIN("/update");
    GP.TEXT("txt", "Город", gorod , "font20 fontyellow_c79536"); GP.BREAK();
    GP.TEXT("txt1", "Широта", latitude , "font20 fontyellow_c79536"); GP.BREAK();
    GP.TEXT("txt2", "Долгота", longitude , "font20 fontyellow_c79536"); GP.BREAK();
    GP.TEXT("txt3", "Ключ API", api_key , "font20 fontyellow_c79536"); GP.BREAK();
    GP.HR();
    GP.LABEL("ПОГОДА", "font16 fontcyan_16747a"); GP.BREAK();
    GP.LABEL("ВЫКЛ.", "font16 fontred_a5381b"); GP.SWITCH("swflagPogoda", flagPogoda); GP.LABEL(" ВКЛ.", "font16 fontred_a5381b"); GP.BREAK();
    GP.HR();
    GP.SUBMIT("💾 СОХРАНИТЬ ", "backgroundred_a5381b widthauto height30 font20 fontblue_000000");
    GP.HR();
    GP.FORM_END();
    GP.HR();
    GP.BUTTON_LINK("/", "МЕНЮ", "backgroundyellow_c79536 width60 height30 font20 fontblue_264280 borderradius50");

    } else if (portal.uri() == "/update1") {
    GP.FORM_BEGIN("/update1");
    GP.HR();
    GP.LABEL("🔧НАСТРОЙКИ🔧", "font20 fontcyan_16747a"); GP.BREAK();
    GP.HR();
    GP.LABEL("RTC", "font16 fontcyan_16747a"); GP.BREAK();
    GP.LABEL("ВЫКЛ.", "font16 fontred_a5381b"); GP.SWITCH("swswtRTC", swtRTC); GP.LABEL(" ВКЛ.", "font16 fontred_a5381b"); GP.BREAK();
    GP.HR();
    GP.LABEL("РАЗДЕЛИТЕЛИ", "font16 fontcyan_16747a"); GP.BREAK();
    GP.LABEL("ТОЧКИ.", "font16 fontred_a5381b"); GP.SWITCH("swflagToch", flagToch); GP.LABEL(" КРЕСТ.", "font16 fontred_a5381b"); GP.BREAK();
    GP.HR();
    GP.LABEL("ЯРКОСТЬ", "font16 fontcyan_16747a"); GP.BREAK();
    GP.LABEL("УРОВЕНЬ", "font16 fontyellow_c79536"); GP.BREAK();
    GP.SLIDER("sldyar", yar, 0, 10); GP.BREAK();
    GP.HR();
    GP.LABEL("СТРОКА", "font16 fontcyan_16747a"); GP.BREAK();
    GP.LABEL("СКОРОСТЬ", "font16 fontyellow_c79536"); GP.BREAK();
    GP.SLIDER("sldq", sk, 10, 60); GP.BREAK();
    GP.HR();
    GP.LABEL("ШРИФТ", "font20 fontgreen_4CAF50"); GP.SELECT("selchrift", "ТОНКИЙ,ТОНКИЙ-ВЫСОКИЙ,ТОЛСТЫЙ", chrift); GP.BREAK(); //
     GP.HR();
    GP.FORM_END();
    GP.BUTTON_LINK("/", "МЕНЮ", "backgroundyellow_c79536 width60 height30 font20 fontblue_264280");//chrift

    } else if (portal.uri() == "/update2") {
    GP.FORM_BEGIN("/update2");
    GP.HR();
    GP.LABEL("🌡ДОМАШНИЕ ДАТЧИКИ🌡", "font20 fontcyan_16747a"); GP.BREAK();
    GP.HR();
    GP.LABEL("ВНИМАНИЕ!!! ВЫБИРАТЬ ТОЛЬКО", "font16 fontred_a5381b"); GP.BREAK();
    GP.LABEL("ПОДКЛЮЧЕННЫЕ ДАТЧИКИ", "font16 fontred_a5381b"); GP.BREAK();
    GP.LABEL("BMP180...", "font16 fontcyan_16747a"); GP.LED_GREEN("led3", M4); GP.LABEL("AHTxx..", "font16 fontcyan_16747a"); GP.LED_GREEN("led1", M2); GP.BREAK();
    GP.LABEL("BMP280..", "font16 fontcyan_16747a"); GP.LED_GREEN("led2", M3); GP.LABEL("GY21....", "font16 fontcyan_16747a"); GP.LED_GREEN("led4", M5); GP.BREAK();
    GP.LABEL("BME280..", "font16 fontcyan_16747a"); GP.LED_GREEN("led", M1); 
    GP.HR();
    GP.LABEL("ТЕМПЕРАТУРЫ", "font20 fontgreen_4CAF50"); GP.SELECT("selt", "NO,  BME280, AHTxx, BMP280, BMP180, GY21", wett); GP.BREAK(); //
    GP.LABEL("КОРРЕКЦИЯ", "font16 fontyellow_c79536"); GP.BREAK();
    GP.SLIDER("sldct", CorTemp, -10, 10); GP.BREAK();
    GP.HR();
    GP.LABEL("ВЛАЖНОСТИ....", "font20 fontgreen_4CAF50"); GP.SELECT("selh", "NO,  BME280, AHTxx, WM, GY21", weth); GP.BREAK(); //
    GP.LABEL("КОРРЕКЦИЯ", "font16 fontyellow_c79536"); GP.BREAK();
    GP.SLIDER("sldch", CorHum, -10, 10); GP.BREAK();
    GP.HR();
    GP.LABEL("ДАВЛЕНИЯ......", "font20 fontgreen_4CAF50"); GP.SELECT("selp", "NO,  BME280, WM, BMP280, BMP180", wetp); GP.BREAK(); // посл sel
    GP.LABEL("КОРРЕКЦИЯ", "font16 fontyellow_c79536"); GP.BREAK();
    GP.SLIDER("sldcp", corrPress, -20, 20); GP.BREAK();
    GP.HR();
    GP.FORM_END();
    GP.BUTTON_LINK("/", "МЕНЮ", "backgroundyellow_c79536 width60 height30 font20 fontblue_264280");


     } else if (portal.uri() == "/update3") {
    GP.HR();
    GP.LABEL("🌏 АФОРИЗМЫ и КУРСЫ ВАЛЮТ 🌏", "font20 fontcyan_16747a");
    GP.HR();
    GP.FORM_BEGIN("/update3");
    GP.LABEL("АФОРИЗМЫ", "font16 fontcyan_16747a"); GP.BREAK();
    GP.LABEL("ВЫКЛ.", "font16 fontred_a5381b"); GP.SWITCH("swchut", flagAforizm); GP.LABEL(" ВКЛ.", "font16 fontred_a5381b"); GP.BREAK();
    GP.HR();
    GP.LABEL("КУРСЫ ВАЛЮТ", "font16 fontcyan_16747a"); GP.BREAK();
    GP.LABEL("ВЫКЛ.", "font16 fontred_a5381b"); GP.SWITCH("swvalu", flagValute); GP.LABEL(" ВКЛ.", "font16 fontred_a5381b"); GP.BREAK();
    GP.HR();
    GP.FORM_END();
    GP.BUTTON_LINK("/", "МЕНЮ", "backgroundyellow_c79536 width60 height30 font20 fontblue_264280 borderradius50");

    } else if (portal.uri() == "/update4") {
    GP.FORM_BEGIN("/update4");
    GP.HR();
    GP.LABEL("НОЧНОЙ РЕЖИМ", "font20 fontcyan_16747a"); GP.BREAK();
    GP.HR();
    GP.LABEL("ВЫКЛ.", "font16 fontred_a5381b"); GP.SWITCH("swMNR", MNR); GP.LABEL(" ВКЛ.", "font16 fontred_a5381b"); GP.BREAK();
    GP.BREAK();
    GP.LABEL("ВРЕМЯ ВКЛЮЧЕНИЯ", "font16 fontgreen_4CAF50"); GP.BREAK();
    GP.LABEL("ЧАСЫ", "font16 fontred_a5381b"); GP.SELECT("selhNon", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23", hNon); GP.LABEL(" МИНУТЫ", "font16 fontred_a5381b"); GP.SELECT("selmNon", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59", mNon); GP.BREAK(); //
    GP.LABEL("ВРЕМЯ ВЫКЛЮЧЕНИЯ", "font16 fontgreen_4CAF50"); GP.BREAK();
    GP.LABEL("ЧАСЫ", "font16 fontred_a5381b"); GP.SELECT("selhNoff", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23", hNoff); GP.LABEL(" МИНУТЫ", "font16 fontred_a5381b"); GP.SELECT("selmNoff", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59", mNoff); GP.BREAK(); //
    GP.HR();
    GP.FORM_END();
    GP.BUTTON_LINK("/", "МЕНЮ", "backgroundyellow_c79536 width60 height30 font20 fontblue_264280");

    } else if (portal.uri() == "/update5") {
    GP.FORM_BEGIN("/update5");  
    GP.HR();
    GP.LABEL("🎶 ОЗВУЧКА 🎶", "font20 fontcyan_16747a"); GP.BREAK();
    GP.LABEL("🔊 ОЗВУЧИВАНИЕ ВРЕМЕНИ 🔊", "font20 fontcyan_16747a"); GP.BREAK();
    GP.SELECT("selMG", "ЖЕНСКИЙ,МУЖСКОЙ,КУРАНТЫ", MG); GP.BREAK();
    GP.HR();
    GP.LABEL("ГРОМКОСТЬ", "font16 fontyellow_c79536"); GP.BREAK();
    GP.SLIDER("sldY", Y, 0, 30); GP.BREAK();
    GP.HR();
    GP.FORM_END();
    GP.HR();
    GP.BUTTON_LINK("/", "МЕНЮ", "backgroundyellow_c79536 width60 height30 font20 fontblue_264280");

    } else if (portal.uri() == "/update6") {
    GP.FORM_BEGIN("/update6");
    GP.HR();
    GP.LABEL("⏰ БУДИЛЬНИКИ ⏰", "font20 fontcyan_16747a"); GP.BREAK();
    GP.HR();
    GP.LABEL("ПОН.", "font16 fontgreen_4CAF50");GP.LABEL("ВЫКЛ.", "font16 fontred_a5381b"); GP.SWITCH("swBUD1", BUD1); GP.LABEL(" ВКЛ.", "font16 fontred_a5381b"); GP.SELECT("selhBud1", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23", hBud1); GP.LABEL(":", "font16 fontgreen_4CAF50"); GP.SELECT("selmBud1", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59", mBud1); GP.BREAK(); 
    GP.LABEL("МЕЛОДИЯ", "font20 fontgreen_4CAF50"); GP.SELECT("selPaB1", "NO, 1,  2, 3, 4, 5", PaB1); GP.BREAK(); 
    GP.HR();
    GP.LABEL("ВТР.", "font16 fontgreen_4CAF50");GP.LABEL("ВЫКЛ.", "font16 fontred_a5381b"); GP.SWITCH("swBUD2", BUD2); GP.LABEL(" ВКЛ.", "font16 fontred_a5381b"); GP.SELECT("selhBud2", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23", hBud2); GP.LABEL(":", "font16 fontgreen_4CAF50"); GP.SELECT("selmBud2", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59", mBud2); GP.BREAK(); 
    GP.LABEL("МЕЛОДИЯ", "font20 fontgreen_4CAF50"); GP.SELECT("selPaB2", "NO, 1,  2, 3, 4, 5", PaB2); GP.BREAK(); 
    GP.HR();
    GP.LABEL("СРД.", "font16 fontgreen_4CAF50");GP.LABEL("ВЫКЛ.", "font16 fontred_a5381b"); GP.SWITCH("swBUD3", BUD3); GP.LABEL(" ВКЛ.", "font16 fontred_a5381b"); GP.SELECT("selhBud3", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23", hBud3); GP.LABEL(":", "font16 fontgreen_4CAF50"); GP.SELECT("selmBud3", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59", mBud3); GP.BREAK(); 
    GP.LABEL("МЕЛОДИЯ", "font20 fontgreen_4CAF50"); GP.SELECT("selPaB3", "NO, 1,  2, 3, 4, 5", PaB3); GP.BREAK(); 
    GP.HR();
    GP.LABEL("ЧТВ.", "font16 fontgreen_4CAF50");GP.LABEL("ВЫКЛ.", "font16 fontred_a5381b"); GP.SWITCH("swBUD4", BUD4); GP.LABEL(" ВКЛ.", "font16 fontred_a5381b"); GP.SELECT("selhBud4", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23", hBud4); GP.LABEL(":", "font16 fontgreen_4CAF50"); GP.SELECT("selmBud4", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59", mBud4); GP.BREAK(); 
    GP.LABEL("МЕЛОДИЯ", "font20 fontgreen_4CAF50"); GP.SELECT("selPaB4", "NO, 1,  2, 3, 4, 5", PaB4); GP.BREAK(); 
    GP.HR();
    GP.LABEL("ПТН.", "font16 fontgreen_4CAF50");GP.LABEL("ВЫКЛ.", "font16 fontred_a5381b"); GP.SWITCH("swBUD5", BUD5); GP.LABEL(" ВКЛ.", "font16 fontred_a5381b"); GP.SELECT("selhBud5", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23", hBud5); GP.LABEL(":", "font16 fontgreen_4CAF50"); GP.SELECT("selmBud5", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59", mBud5); GP.BREAK(); 
    GP.LABEL("МЕЛОДИЯ", "font20 fontgreen_4CAF50"); GP.SELECT("selPaB5", "NO, 1,  2, 3, 4, 5", PaB5); GP.BREAK(); 
    GP.HR();
    GP.LABEL("СБТ.", "font16 fontred_a5381b");GP.LABEL("ВЫКЛ.", "font16 fontred_a5381b"); GP.SWITCH("swBUD6", BUD6); GP.LABEL(" ВКЛ.", "font16 fontred_a5381b"); GP.SELECT("selhBud6", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23", hBud6); GP.LABEL(":", "font16 fontgreen_4CAF50"); GP.SELECT("selmBud6", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59", mBud6); GP.BREAK(); 
    GP.LABEL("МЕЛОДИЯ", "font20 fontgreen_4CAF50"); GP.SELECT("selPaB6", "NO, 1,  2, 3, 4, 5", PaB6); GP.BREAK(); 
    GP.HR();
    GP.LABEL("ВСК.", "font16 fontred_a5381b");GP.LABEL("ВЫКЛ.", "font16 fontred_a5381b"); GP.SWITCH("swBUD7", BUD7); GP.LABEL(" ВКЛ.", "font16 fontred_a5381b"); GP.SELECT("selhBud7", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23", hBud7); GP.LABEL(":", "font16 fontgreen_4CAF50"); GP.SELECT("selmBud7", "00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59", mBud7); GP.BREAK(); 
    GP.LABEL("МЕЛОДИЯ", "font20 fontgreen_4CAF50"); GP.SELECT("selPaB7", "NO, 1,  2, 3, 4, 5", PaB7); GP.BREAK(); 
    GP.HR();
    GP.FORM_END();
    GP.HR();
    GP.BUTTON_LINK("/", "МЕНЮ", "backgroundyellow_c79536 width60 height30 font20 fontblue_264280");


    }else {
    GP.HR();
    GP.BUTTON_LINK("/update", "🧭 ПОГОДА ", "backgroundyellow_c79536 width350 height30 font20 fontred_a5381b"); GP.BREAK();
    GP.BUTTON_LINK("/update1", "🔧 НАСТРОЙКИ ", "backgroundyellow_c79536 width350 height30 font20 fontred_a5381b"); GP.BREAK();
    GP.BUTTON_LINK("/update2", "🌡 ДАТЧИКИ ", "backgroundyellow_c79536 width350 height30 font20 fontred_a5381b"); GP.BREAK();
    GP.BUTTON_LINK("/update3", "🌏 АФОРИЗМЫ и КУРСЫ ", "backgroundyellow_c79536 width350 height30 font20 fontred_a5381b"); GP.BREAK();
    GP.BUTTON_LINK("/update4", "🌃 НОЧНОЙ РЕЖИМ ", "backgroundyellow_c79536 width350 height30 font20 fontred_a5381b"); GP.BREAK();
    GP.BUTTON_LINK("/update5", "🔊 ОЗВУЧКА ", "backgroundyellow_c79536 width350 height30 font20 fontred_a5381b"); GP.BREAK(); 
    GP.BUTTON_LINK("/update6", "⏰ БУДИЛЬНИКИ ", "backgroundyellow_c79536 width350 height30 font20 fontred_a5381b"); GP.BREAK();
    GP.HR();
    GP.LABEL("COM порт ВЫКЛ.", "font16 fontcyan_16747a"); GP.SWITCH("swcom", printCom); GP.LABEL(" COM порт ВКЛ.", "font16 fontcyan_16747a"); add.BREAK();
    GP.HR();
    GP.BUTTON("btnrst", "↺ RESET", "backgroundred_a5381b widthauto height30 font20 fontblue_000000 borderradius50"); add.BREAK();
    GP.HR();    
    GP.LABEL("ver.⓵_max7219", "font16 fontred_a5381b"); GP.BREAK();//⓵⓶⓷⓸⓹⓺⓻⓼⓽⓾

   }
   BUILD_END();
}
