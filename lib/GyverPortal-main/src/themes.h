#pragma once
// стили для конструктора страниц GyverPortal

const char GP_LIGHT[] PROGMEM =
"<style type=\"text/css\">\n"
"body {font-family: sans-serif;margin-top:15px;}\n"
"hr {width:95%;margin-bottom:10px;max-width:400px;}\n"
"h2 {margin:8px 0;}\n"
"span {font-size:20px;}\n"
"label {font-size:20px;margin:0 5px;}\n"
".chartBlock {border-radius:15px;margin:10px;width:90%;max-width:1000px;height:500px}\n"
".block {border-radius:10px;background-color:#f2f2f2;padding:15px 0px;margin-top:3px;margin-bottom:15px;width:90%;max-width:400px;}\n"
".sldBlock{width:90%;display:flex;flex-direction:row;justify-content:right;align-items:center}"
".sldLbl{font-size:15px;}"
"input[type=\"number\"],input[type=\"text\"],input[type=\"password\"],input[type=\"date\"],input[type=\"time\"],input[type=\"range\"],input[type=\"color\"],input[type=\"checkbox\"],select,textarea\n"
"{border-radius:8px;max-width:350px;padding:3px 10px;vertical-align:middle;position:relative;margin:2px 0 7px 0;font-size:20px;height:40px;cursor:pointer;}\n"
"input[type=\"range\"] {width:60%;height:30px;padding:0px;}\n"
"input[type=\"date\"],input[type=\"time\"] {width:180px;}\n"
"input[type=\"color\"] {width:100px;height:40px;}\n"
"input[type=\"checkbox\"] {width:27px;height:27px;margin-bottom:10px;}\n"
"input[type=\"number\"],input[type=\"text\"],input[type=\"password\"],select,textarea {display:inline-block;border:1px solid #ccc;border-radius:8px;box-sizing:border-box;cursor:auto;}\n"
"input[type=\"submit\"],input[type=\"button\"] {max-width:350px;height:60px;font-size:28px;width:90%;margin:8px 5px;background-color:#4CAF50;border:none;border-radius:8px;color:white;cursor:pointer;padding:0px 10px;}\n"
"input[type=submit],input[type=\"button\"]:hover {background-color:#45a049;}\n"
"textarea {width: 100%;}"
".led {margin:20px 18px;}\n"
".led:after {width:25px;height:25px;border-radius:25px;top:-10px;left:-9px;position:relative;content:'';display:inline-block;border:2px solid;border-color:#858585;background-color:#323232}\n"
".led:checked:after {box-shadow:0px 0px 10px;}\n"
".led.red:checked:after {border-color:red !important;color:red !important;background-color:red !important;}\n"
".led.green:checked:after {border-color:lime !important;color:lime !important;background-color:lime !important;}\n"
".miniButton{height:40px !important;font-size:20px!important;width:auto!important;}\n"
".switch{margin:10px 0 5px;position:relative;display:inline-block;width:60px;height:34px}\n"
".switch input{opacity:0;width:0;height:0}\n"
".slider{border-radius:34px;position:absolute;cursor:pointer;top:-5px;left:0;right:0;bottom:5px;background-color:#ccc;-webkit-transition:.1s;transition:.1s}\n"
".slider:before{border-radius:50%;position:absolute;content:\"\";height:26px;width:26px;left:4px;bottom:4px;background-color:#fff;-webkit-transition:.1s;transition:.1s}\n"
"input:checked+.slider{background-color:#2196f3}\n"
"input:checked+.slider:before{-webkit-transform:translateX(26px);-ms-transform:translateX(26px);transform:translateX(26px)}\n"
"</style>\n";

const char GP_DARK[] PROGMEM =
"<style type=\"text/css\">\n"
"#blockBack>input[type=\"password\"]{background:#13161a}\n"
"#blockBack>input[type=\"text\"]{background:#13161a}\n"
"#blockBack>input[type=\"date\"]{background:#13161a}\n"
"#blockBack>input[type=\"time\"]{background:#13161a}\n"
"#blockBack>input[type=\"number\"]{background:#13161a}\n"
"#blockBack>select{background:#13161a}\n"
"body {font-family:sans-serif;background:#13161a;color:#bbb;margin-top:15px;}\n"
"hr {width:95%;margin-bottom:10px;border:none;border-top:2px solid #394048;max-width:400px;}\n"
"h2 {margin:8px 0;}\n"
"span {font-size:20px;}\n"
"label {font-size:20px;margin:0 5px;}\n"
".chartBlock {border-radius:15px;margin:10px;width:90%;max-width:1000px;height:500px}\n"
".block {border-radius:10px;background-color:#2a2d35;padding:15px 0px;margin-top:3px;margin-bottom:15px;width:90%;max-width:400px;}\n"
".sldBlock{width:90%;display:flex;flex-direction:row;justify-content:right;align-items:center}"
".sldLbl{font-size:15px;}"
"input[type=\"number\"],input[type=\"text\"],input[type=\"password\"],input[type=\"date\"],input[type=\"time\"],input[type=\"range\"],input[type=\"color\"],input[type=\"checkbox\"],select,textarea\n"

"{border-radius:8px;max-width:350px;padding:3px 10px;color:#bbb;border:none;background-color:#2a2d35;vertical-align:middle;position:relative;margin:2px 0 7px 0;font-size:20px;height:40px;cursor:pointer;}\n"
//"{border-radius:8px;max-width:350px;padding:3px 10px;color:#bbb;border:none;background-color:#a5381b;vertical-align:middle;position:relative;margin:2px 0 7px 0;font-size:20px;height:40px;cursor:pointer;}\n"

"input[type=\"range\"] {width:60%;height:30px;padding:0px;}\n"
"input[type=\"date\"],input[type=\"time\"] {width:180px;}\n"
"input[type=\"color\"] {width:100px;height:40px;}\n"
"input[type=\"checkbox\"] {width:27px;height:27px;margin-bottom:10px;}\n"
"input[type=\"number\"],input[type=\"text\"],input[type=\"password\"],select,textarea {display:inline-block;border-radius:8px;box-sizing:border-box;cursor:auto;}\n"

//"input[type=\"submit\"],input[type=\"button\"] {max-width:350px;height:60px;font-size:28px;width:90%;margin:8px 5px;background-color:#4CAF50;border:none;border-radius:8px;color:white;cursor:pointer;}\n"//green
//"input[type=\"submit1\"],input[type=\"button1\"] {max-width:350px;height:60px;font-size:28px;width:90%;margin:8px 5px;background-color:#a5381b;border:none;border-radius:8px;color:white;cursor:pointer;}\n"//red
"input[type=\"submit\"],input[type=\"button\"] {max-width:350px;height:60px;font-size:28px;width:90%;margin:8px 5px;background-color:#115b60;border:none;border-radius:8px;color:white;cursor:pointer;}\n"//cyan

//"input[type=submit],input[type=\"button\"]:hover {background-color:#45a049;}\n"//green
//"input[type=submit1],input[type=\"button\"]:hover {background-color:#a5381b;}\n"//red
"input[type=submit],input[type=\"button\"]:hover {background-color:#1d315f;}\n"//blue
//"input[type=submit],input[type=\"button\"]:hover {background-color:#115b60;}\n"//cyan
// Изменено

"input[type=\"button\"] {max-width:320px;height:60px;font-size:28px;width:90%;margin:8px 5px;background-color:#4CAF50;border:none;border-radius:8px;color:white;cursor:pointer;padding:0px 10px;box-shadow: 1px 1px 0 #ccc,2px 2px 0 #c9c9c9,3px 4px 0 #bbb, -1px 1px 0 #ccc,-2px 2px 0 #c9c9c9,-3px 4px 0 #bbb!important;}\n"
//"input[type=\"button\"] {max-width:320px;height:60px;font-size:28px;width:90%;margin:8px 5px;background-color:#4CAF50;border:none;border-radius:8px;color:white;cursor:pointer;padding:0px 10px;box-shadow: 1px 1px 0 #ccc,2px 2px 0 #c9c9c9,3px 4px 0 #bbb, -1px 1px 0 #ccc,-2px 2px 0 #c9c9c9,-3px 4px 0 #bbb!important;}\n"
"input[type=\"submit\"] {max-width:320px;height:60px;font-size:28px;width:90%;margin:8px 5px;background-color:#4CAF50;border:none;border-radius:8px;color:white;cursor:pointer;padding:0px 10px;box-shadow: 1px 1px 0 #ccc,2px 2px 0 #c9c9c9,3px 4px 0 #bbb, -1px 1px 0 #ccc,-2px 2px 0 #c9c9c9,-3px 4px 0 #bbb!important;}\n"
		
// Свойства компонентов

//Ширина компонентов
".width40 {max-width:40px!important;}\n" //для кнопки мини, чтобы сделать ее квадратной
".width50 {max-width:50px!important;}\n"
".width60 {max-width:60px!important;}\n" //для кнопки, чтобы сделать ее квадратной
".width100 {max-width:100px!important;}\n"
".width150 {max-width:150px!important;}\n"
".width200 {max-width:200px!important;}\n"
".width250 {max-width:250px!important;}\n"
".width300 {max-width:300px!important;}\n"
".width320 {max-width:320px!important;}\n" // чтобы поместились 3 кнопки в строку
".width350 {max-width:350px!important;}\n"
".width400 {max-width:450px!important;}\n"
".widthauto {width:auto!important;}\n"
//Сюда ниже можете добавить свою ширину:
".width140 {max-width:140px!important;}\n"
".width135 {max-width:135px!important;}\n"
".width20 {max-width:20px!important;}\n"

//-----------------------------------
//Высота компонентов
".height30 {height:30px!important;}\n" 
".height50 {height:50px!important;}\n" 
".height70 {height:70px!important;}\n" 
".height100 {height:100px!important;}\n" 
".height150 {height:150px!important;}\n" 
".height200 {height:200px!important;}\n"
".height250 {height:250px!important;}\n" 
".height300 {height:300px!important;}\n"  
".height350 {height:350px!important;}\n" 
".heightauto {height:auto!important;}\n" 

//---------------------------------------
//Высота шрифта
".font8 {font-size:8px!important;}\n"
".font16 {font-size:16px!important;}\n"
".font20 {font-size:20px!important;}\n"
".font25 {font-size:25px!important;}\n"
".font30 {font-size:30px!important;}\n"
".font40 {font-size:40px!important;}\n"
".font60 {font-size:60px!important;}\n"
".font80 {font-size:80px!important;}\n"
".font100 {font-size:100px!important;}\n"
".font150 {font-size:150px!important;}\n"
".font200 {font-size:200px!important;}\n"
".font250 {font-size:250px!important;}\n"

//-------------------------------------
//Цвет шрифта
".fontgreen_4CAF50 {color:#4CAF50!important;}\n"
".fontblue_264280 {color:#264280!important;}\n"
".fontblue_0000ff {color:#0000ff!important;}\n"
".fontcyan_16747a {color:#16747a!important;}\n"
".fontyellow_c79536 {color:#c79536!important;}\n"
".fontgrey_777777 {color:#777777!important;}\n"
".fontred_a5381b {color:#a5381b!important;}\n"
".fontpurpe_5c3580 {color:#5c3580!important;}\n"

//Цвет фона компонента
".backgroundgreen_4CAF50 {background-color:#4CAF50!important;}\n" //установка цвета кнопки, имя цвет + HEX цвета
".backgroundgreen_4CAF50:hover {background-color:#45a049 !important;}\n" // изменение (потемнение) цвета при наведении курсора
".backgroundblue_264280 {background-color:#264280 !important;}\n"
".backgroundblue_264280:hover {background-color:#1d315f !important;}\n"
".backgroundcyan_16747a {background-color:#16747a !important;}\n"
".backgroundcyan_16747a:hover {background-color:#115b60 !important;}\n"
".backgroundyellow_c79536 {background-color:#c79536 !important;}\n"
".backgroundyellow_c79536:hover {background-color:#a97f2e !important;}\n"
".backgroundgrey_777777 {background-color:#777777 !important;}\n"
".backgroundgrey_777777:hover {background-color:#606060 !important;}\n"
".backgroundred_a5381b {background-color:#a5381b !important;}\n"
".backgroundred_a5381b:hover {background-color:#8b2f17 !important;}\n"
".backgroundpurpe_5c3580 {background-color:#5c3580 !important;}\n"
".backgroundpurpe_5c3580:hover {background-color:#452760 !important;}\n"
//Сюда ниже можете добавить свои цвета:

//-----------------------------------
//Цвет с градиентом:
".backgroundred_gradient {background:linear-gradient(top,#f58f99,#bf1e2e)!important;background:-webkit-linear-gradient(top,#f58f99,#bf1e2e)!important; /* для Chrome и Safari */background:-o-linear-gradient(top,#f58f99,#bf1e2e)!important; /* для Opera */background:-moz-linear-gradient(top,#f58f99,#bf1e2e)!important; /* для Firefox */background:-ms-linear-gradient(top,#f58f99,#bf1e2e)!important; /* для IE10+ */text-decoration: none!important;}\n" 
".backgroundred_gradient:hover {background:linear-gradient(bottom,#f58f99,#bf1e2e)!important; background:-webkit-linear-gradient(bottom, #f58f99 5%,#bf1e2e)!important; /* для Chrome и Safari */ background:-o-linear-gradient(bottom,#f58f99,#bf1e2e)!important;/* для Opera */ background:-moz-linear-gradient(bottom,#f58f99,#bf1e2e)!important; /* для Firefox */ background:-ms-linear-gradient(bottom,#f58f99,#bf1e2e)!important; /* для IE10+ */ text-decoration: none!important;}\n" 
".backgroundgreen_gradient {background:linear-gradient(top,#9ACD32,#228B22)!important;background:-webkit-linear-gradient(top,#9ACD32,#228B22)!important;/* для Chrome и Safari */ background:-o-linear-gradient(top,#f4da71,#cca509)!important; /* для Opera */ background:-moz-linear-gradient(top,#f4da71,#cca509)!important; /* для Firefox */ background:-ms-linear-gradient(top,#f4da71,#cca509)!important; /* для IE10+ */text-decoration: none!important; }\n"  
".backgroundgreen_gradient:hover {background:linear-gradient(bottom,#9ACD32,#228B22)!important;background:linear-gradient(bottom,#9ACD32,#228B22)!important;  background:-webkit-linear-gradient(bottom, #9ACD32 5%,#228B22)!important;/* для Chrome и Safari */ background:-o-linear-gradient(bottom,#9ACD32,#228B22)!important; /* для Opera */ background:-moz-linear-gradient(bottom,#9ACD32,#228B22)!important; /* для Firefox */ background:-ms-linear-gradient(bottom,#9ACD32,#228B22)!important; /* для IE10+ */text-decoration: none!important;}\n"
".backgroundyellow_gradient {background:linear-gradient(top,#f4da71,#cca509)!important; background:-webkit-linear-gradient(top,#f4da71,#cca509)!important; /* для Chrome и Safari */ background:-o-linear-gradient(top,#f4da71,#cca509)!important; /* для Opera */ background:-moz-linear-gradient(top,#f4da71,#cca509)!important; /* для Firefox */ background:-ms-linear-gradient(top,#f4da71,#cca509)!important; /* для IE10+ */ text-decoration: none!important;}\n" 
".backgroundyellow_gradient:hover {background:linear-gradient(bottom,#f4da71,#cca509)!important;background:-webkit-linear-gradient(bottom, #f4da71 5%,#cca509)!important; /* для Chrome и Safari */ background:-o-linear-gradient(bottom,#f4da71,#cca509)!important; /* для Opera */ background:-moz-linear-gradient(bottom,#f4da71,#cca509)!important; /* для Firefox */ background:-ms-linear-gradient(bottom,#f4da71,#cca509)!important; /* для IE10+ */ text-decoration: none!important;}\n" 
//Сюда ниже можете добавить свои цвета:

//----------------------------------
//Рисунок установить фоном страницы (выберите легкие рисунки)
".backgroundimage {background: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEoAAAA/AQMAAAB98cxAAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAADsMAAA7DAcdvqGQAAAAGUExURQAAAP///6XZn90AAAD5SURBVBgZBcGxjdwwEADAIRQwMaAOfjsh23LwODFzWyxF7oDAB2YgaD0DAADgN+qAmpNrQ+Ry5AtXPmrmQOYrMicl/6S+r5vjcY1rnIu69JmOTb2dfx9lc071Z/NwTse/xTcxlLz5EMhJI5CDRuAaNDo6goaOoOELQcMvBA0QNEDQAEEAOgFoBKARgEYM4MM5gG/OCTzUCWzqDcqm3qBsjgWORVngWJQN6o0H1IkHnBMfEAMddOgDLogJL5w3ygN14dhwbNQF5cF5gxcxwTW4BuiTBGIpL3Bu9QGOVyygpH4DcuYE9J8EOPMBqLkBSt4ArgHgCwAAAP8BXuJx0+fxIvoAAAAASUVORK5CYII=) !important;}\n"

//рисунок фона по ссылке, три строки вставляют и растягивают изображение для фона
".backgroundimage1 {background: url(https://kartinkin.net/uploads/posts/2021-07/1626904456_4-kartinkin-com-p-staroe-radio-art-art-krasivo-5.jpg) !important;"
"background-repeat: no-repeat !important;background-position: center center !important;background-attachment: fixed !important;"
"-webkit-background-size: cover !important;-moz-background-size: cover !important;-o-background-size: cover !important;background-size: cover !important;}\n"

".backgroundimage2 {background: url(https://sharij.news/wp-content/uploads/2017/01/c0daae98380a5f0e53da8f4153aaa4fa.jpg) !important;"
"background-repeat: no-repeat !important;background-position: center center !important;background-attachment: fixed !important;"
"-webkit-background-size: cover !important;-moz-background-size: cover !important;-o-background-size: cover !important;background-size: cover !important;}\n"

".backgroundimage3 {background-image:url(https://on-desktop.com/wps/World_Travel___Tourism_Scoreboard_departures_and_arrivals_018987_.jpg) !important;"
"background-repeat: no-repeat !important;background-position: center center !important;background-attachment: fixed !important;"
"-webkit-background-size: cover !important;-moz-background-size: cover !important;-o-background-size: cover !important;background-size: cover !important;}\n"

".backgroundimage4 {background-image:url(https://tehnofaq.ru/wp-content/uploads/2022/03/20190109101909-51f48891-xl.jpg) !important;"
"background-repeat: no-repeat !important;background-position: center center !important;background-attachment: fixed !important;"
"-webkit-background-size: cover !important;-moz-background-size: cover !important;-o-background-size: cover !important;background-size: cover !important;}\n"

".backgroundimage5 {background-image:url(https://img.infonex.ru/wp-content/uploads/2019/10/29143015/Servisy.jpg) !important;"
"background-repeat: no-repeat !important;background-position: center center !important;background-attachment: fixed !important;"
"-webkit-background-size: cover !important;-moz-background-size: cover !important;-o-background-size: cover !important;background-size: cover !important;}\n"

".backgroundimage6 {background-image:url(http://puschino.omsu.inlite.ru/files/image/34/37/35/lg!to0.jpg) !important;"
"background-repeat: no-repeat !important;background-position: center center !important;background-attachment: fixed !important;"
"-webkit-background-size: cover !important;-moz-background-size: cover !important;-o-background-size: cover !important;background-size: cover !important;}\n"

".backgroundimage7 {background-image:url(http://pics2.pokazuha.ru/p201/5/y/11202969iy5.jpg) !important;"
"background-repeat: no-repeat !important;background-position: center center !important;background-attachment: fixed !important;"
"-webkit-background-size: cover !important;-moz-background-size: cover !important;-o-background-size: cover !important;background-size: cover !important;}\n"

".backgroundimage8 {background-image:url(https://c.pxhere.com/photos/ec/c9/clock_old_time_antique_vintage_watch_aged_retro-660342.jpg!d) !important;"
"background-repeat: no-repeat !important;background-position: center center !important;background-attachment: fixed !important;"
"-webkit-background-size: cover !important;-moz-background-size: cover !important;-o-background-size: cover !important;background-size: cover !important;}\n"
//----------------------

// Выравнивание компонента
".position_left {position:relative !important;right: 335px !important;}\n" 
".position_right {position:relative !important;left: 335px !important;}\n" 
".positiontop_btn {top: 100px !important;}\n" 

// Радиус закруглений углов
".borderradius25 {border-radius:25px !important;}\n"
".borderradius50 {border-radius:50px !important;}\n"
".borderradius75 {border-radius:75px !important;}\n"

//Нажатие кнопки:
"input[type=\"button\"]:hover {text-decoration: none!important;color: #fff!important!important;} \n"
"input[type=\"submit\"]:hover {text-decoration: none!important;color: #fff!important!important;} \n" 
"input[type=\"button\"]:active {box-shadow: 0 1px 0 rgba(255, 255, 255, .5) inset, 0 -1px 0 rgba(255, 255, 255, .1)inset!important;box-shadow:0 1px 0 rgba(255, 255, 255, .5) inset, 0 -1px 0 rgba(255, 255, 255, .1)inset!important; -moz-transform: translatey(3px)!important; /* Для Firefox */ -ms-transform: translatey(3px)!important; /* Для IE */ -webkit-transform: translatey(3px)!important; /* Для Safari, Chrome, iOS */ -o-transform:translatey(3px)!important; /* Для Opera */transform: translatey(3px)!important;}\n"
"input[type=\"submit\"]:active {box-shadow: 0 1px 0 rgba(255, 255, 255, .5) inset, 0 -1px 0 rgba(255, 255, 255, .1)inset!important;box-shadow:0 1px 0 rgba(255, 255, 255, .5) inset, 0 -1px 0 rgba(255, 255, 255, .1)inset!important; -moz-transform: translatey(3px)!important; /* Для Firefox */ -ms-transform: translatey(3px)!important; /* Для IE */ -webkit-transform: translatey(3px)!important; /* Для Safari, Chrome, iOS */ -o-transform:translatey(3px)!important; /* Для Opera */transform: translatey(3px)!important;}\n"

//конец изменений---------------------------------

"input:focus,select,textarea:focus{outline:none;}"
"textarea {width: 100%;}"
".led {margin:20px 18px;}\n"
".led:after {width:25px;height:25px;border-radius:25px;top:-10px;left:-9px;position:relative;content:'';display:inline-block;border:2px solid;border-color:#858585;background-color:#121212}\n"
".led:checked:after {box-shadow:0px 0px 10px 4px;}\n"
".led.red:checked:after {border-color:red !important;color:red !important;background-color:red !important;}\n"
".led.green:checked:after {border-color:lime !important;color:lime !important;background-color:lime !important;}\n"
".miniButton{height:40px !important;font-size:20px!important;width:auto!important;}\n"

".switch{margin:10px 0 5px;position:relative;display:inline-block;width:50px;height:6px}\n"
".switch input{opacity:0;width:0;height:0}\n"
".slider{border-radius:34px;position:absolute;cursor:pointer;top:0px;left:0;right:0;bottom:-14px;background-color:#54545485;-webkit-transition:.1s;transition:.1s}\n"
".slider:before{border-radius:50%;position:absolute;content:\"\";height:20px;width:20px;left:4px;bottom:0px;background-color:#fff;-webkit-transition:.1s;transition:.1s}\n"
"input:checked+.slider{background-color:#2196f3}\n"
"input:checked+.slider:before{-webkit-transform:translateX(22px);-ms-transform:translateX(22px);transform:translateX(22px)}\n"
".sldLblValue{font-size:20px;color:#00BFFF;padding:8px;border-radius:10px;background-color:#343e40;}\n"
"</style>\n";

