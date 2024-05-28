/*
    Простой конструктор веб интерфейса для esp8266 и ESP32
    Документация:
    GitHub: https://github.com/GyverLibs/GyverPortal
    Возможности:
    - Простой конструктор - делаем страницы без знаний HTML и CSS
    - Библиотека является обёрткой для стандартной ESP8266WebServer
    - Позволяет быстро создать вебморду для управления и настройки своего девайса
    - Компактный читаемый код в "скетче", никаких внешних обработчиков и лямбда-функций
    - Конструктор использует стандартные HTML формы, CSS и javascript
    - Элементы конструктора хранятся во Flash памяти
    - Никаких глобальных буферов, всё генерируется на лету
    - Приятный дизайн из коробки + тёмная тема
    - Адаптировано под мобильные устройства и ПК
    - Встроенные инструменты для удобного парсинга значений с формы
    - Возможность настроить автоматическое обновление значений переменных по действию со страницы
    - Встроенные жабаскрипты для AJAX, работа без обновления всей страницы
    
    v1.0 - релиз
    v1.1 - улучшил графики и стили
    v1.2
    - Блок NUMBER теперь тип number
    - Добавил большое текстовое поле AREA
    - Добавил GPunix
    - Улучшил парсинг
    - Добавил BUTTON_MINI
    - Кнопки могут передавать данные с других компонентов (кроме AREA и чекбоксов)
    - Добавил PLOT_STOCK - статический график с масштабом
    - Добавил AJAX_PLOT_DARK
    - Изменён синтаксис у старых графиков
    - Фичи GPaddUnix и GPaddInt для графиков
    - Убрал default тему
    - Подкрутил стили
    - Добавил окно лога AREA_LOG и функцию лога в целом
    
    v1.3 - переделал GPunix, мелкие фиксы, для списков можно использовать PSTR
    v1.4 - мелкие фиксы, клик по COLOR теперь отправляет цвет
    v1.5 - добавил блок "слайдер+подпись"
    v1.5.1 - мелкий фикс копирования строк
    v1.6 - добавлены инструменты для работы c цветом. Добавил answer() для даты, времени и цвета
    v1.7 - поддержка ESP32
    
    v2.0: Большое обновление! Логика работы чуть изменена, обнови свои скетчи!
    - Много оптимизации/облегчения/ускорения
    - Полная поддержка ESP32
    - Переделана логика опроса действий (более правильно и оптимально + работает на ESP32) с сохранением легаси
    - Убран DateTimeP (не используется в библиотеке) и вынес отдельно в библиотеку DatePack
    - Переделан и облегчен модуль лога (log)
    - Добавлен MDNS, чтобы не искать IP платы в мониторе порта (см. доку)
    - Автоопределение режима работы WiFi. Переделан start() с сохранением легаси (см. доку)
    - Упрощён билдер, строку создавать и передавать не нужно (см. доку)
    - Объект билдера теперь называется GP (вместо add) с сохранением легаси
    - Пофикшены варнинги
    - Добавлены удобства для работы с цветом GPcolor, датой GPdate и временем GPtime
    - Удалены старые функции преобразования цвета и даты-времени (см. доку)
    - Портал теперь возвращает цвет в формате GPcolor, автообновление переменных тоже работает с GPcolor
    - Все примеры протестированы на esp8266 и esp32
    
    v2.1
    - Вернул функции root() и uri() для удобства создания многостраничности
    - Добавлен пример организации многостраничности
    - Добавлена кнопка-ссылка BUTTON_LINK
    - Добавлена авторизация по логину-паролю (см. доку)
    - Добавлено OTA обновление прошивки из браузера, в т.ч. с паролем (см. доку)
*/
/*
    TODO
    https://community.alexgyver.ru/threads/gyverportal.6632/page-2#post-122947
    https://snipp.ru/html-css/style-radio

    канвас
    https://www.w3schools.com/html/html5_canvas.asp
    https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API/Tutorial/Drawing_shapes
    https://developer.mozilla.org/ru/docs/Web/API/Canvas_API/Tutorial/Pixel_manipulation_with_canvas
    https://www.w3schools.com/tags/tryit.asp?filename=tryhtml5_canvas_createimagedata
*/
#ifndef _GyverPortal_h
#define _GyverPortal_h

#ifndef GP_NO_DNS
#include <DNSServer.h>
#endif

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#ifndef GP_NO_MDNS
#include <ESP8266mDNS.h>
#endif
#ifndef GP_NO_OTA
#include <ESP8266HTTPUpdateServer.h>
#endif
#else

#include <WiFi.h>
#include <WebServer.h>
#ifndef GP_NO_MDNS
#include <ESPmDNS.h>
#endif
#ifndef GP_NO_OTA
#include <HTTPUpdateServer.h>
#endif
#endif

#include "themes.h"
#include "list.h"
#include "utils.h"
#include "portal.h"
//String& textNst;
// ======================= БИЛДЕР =======================
struct Builder {
    // ======================= СТРАНИЦА =======================
    void PAGE_BEGIN() {
        *_GP += F("<!DOCTYPE HTML><html><head>\n"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
        "<meta charset=\"utf-8\"></head><body>\n");
    }
    void AJAX_CLICK() {
        *_GP += F("<script>function GP_click(arg){var xhttp=new XMLHttpRequest();var v;\n"
        "if(arg.type==\"checkbox\")v=arg.checked?'1':'0';\nelse v=arg.value;\n"
        "if(v.charAt(0)=='#')v=v.substring(1);\n"
        "xhttp.open(\"POST\",\"GP_click?\"+arg.name+\"=\"+v,true);xhttp.send();}\n"
        "function GP_clickid(btn,tar){var xhttp=new XMLHttpRequest();\n"
        "xhttp.open(\"POST\",\"GP_click?\"+btn+\"=\"+document.getElementById(tar).value,true);xhttp.send();\n}"
        "</script>\n");
    }
    void THEME(const char* style) {
        *_GP += FPSTR(style);
    }
    void PAGE_BLOCK_BEGIN() {
        *_GP += F("<div align=\"center\" style=\"margin:auto;max-width:1000px;\">\n");
    }
    void PAGE_BLOCK_END() {
        *_GP += F("</div>");
    }
    void PAGE_END() {
        *_GP += F("</body></html>");
    }
    void AJAX_UPDATE(const char* list, int prd = 1000) {
        *_GP += F("<script>setInterval(function(){\n");
        *_GP += "var elms=[";
        char buf[strlen(list) + 1];
        strcpy(buf, list);
        char* str = buf;
        splitList(NULL);
        while ((str = splitList(buf)) != NULL) {
            *_GP += "'";
            if (str[0] == ' ') *_GP += (str + 1);
            else *_GP += str;
            *_GP += "',";
        }
        *_GP += F("];\n"
        "elms.forEach(function(elm){\n"
        "var xhttp=new XMLHttpRequest();\n"
        "xhttp.onreadystatechange=function(){\n"
        "if(this.readyState==4&&this.status==200){\n"
        "var resp=this.responseText;\n"
        "var item=document.getElementById(elm);\n"
        "if(item.type==\"checkbox\"||item.type==\"radio\")item.checked=Number(resp);\n"
        "else if(item.type==undefined)item.innerHTML=resp;\n"
        "else item.value=resp;\n"
        "}};xhttp.open(\"GET\",\"GP_update?\"+elm,true);xhttp.send();});},");
        *_GP += prd;
        *_GP += F(");</script>\n");
    }
    void AREA_LOG(int rows = 5) {
        *_GP += F("<textarea style=\"height:auto\" id=\"GP_log\" rows=\"");
        *_GP += rows;
        *_GP += F("\" disabled></textarea>");
        *_GP += F("<script>let _gplog=\"\";\n"
        "setInterval(function(){var xhttp=new XMLHttpRequest();\n"
        "xhttp.onreadystatechange=function(){\n"
        "if(this.readyState==4&&this.status==200){\n"
        "_gplog+=this.responseText;\n"
        "var elm=document.getElementById(\"GP_log\");\n"
        "elm.innerHTML=_gplog;elm.scrollTop=elm.scrollHeight;}};\n"
        "xhttp.open(\"GET\",\"GP_log?\",true);xhttp.send();},1000);</script>\n");
    }
    void AREA(const String& name, int rows = 1, const String& value = "", bool dis = false) {
        *_GP += F("<textarea onchange='GP_click(this)' style='height:auto' name='");
        *_GP += name;
        *_GP += F("' id='");
        *_GP += name;
        *_GP += F("' rows='");
        *_GP += rows;
        *_GP += "'";
        if (dis) *_GP += F(" disabled");
        *_GP += ">";
        if (value.length()) *_GP += value;
        *_GP += F("</textarea>\n");
       
    }
    
    // ======================= ФОРМА =======================
    void FORM_BEGIN(const char* action) {
        *_GP += F("<form action=\"");
        *_GP += action;
        *_GP += F("\" method=\"POST\">\n");
    }
    void FORM_END() {
        *_GP += F("</form>\n");
    }
    void SUBMIT(const char* value,const char* clas) {
        *_GP += F("<input class=\"");
        *_GP += clas;		
        *_GP += F("\" type=\"submit\" value=\"");
        *_GP += value;
        *_GP += F("\">\n");
    }
     void FORM_SUBMIT(const char* name, const char* value,const char* clas) {
        FORM_BEGIN(name);
        SUBMIT(value, clas);
        FORM_END();
    }

    // ======================= ОФОРМЛЕНИЕ =======================
    void BLOCK_BEGIN(const char* name="") {
        *_GP += F("<div class=\"block\" id=\"blockBack\">\n");
        if (name != "") {
            *_GP += F("<div class=\"blockHeader\">");
            *_GP += name;
            *_GP += F("</div>\n");
        }
    }
    void BLOCK_END() {
        *_GP += F("</div>\n");
    }
    void BREAK() {
        *_GP += F("<br>\n");
    }
    void HR() {
        *_GP += F("<hr>\n");
    }
    void BODY(const char* clas) {
        *_GP += F("<body class=\"");	
	    *_GP += clas;
        *_GP += F("\">");		
        *_GP += F("<body>\n");
    }	
    
 //изменено
    void TITLE(const char* name, const char* clas, const char* id="") {
        *_GP += F("<h2 class=\"");
	    *_GP += clas;
        *_GP += "\" id=\"";		
        *_GP += id;
        *_GP += F("\">");
        *_GP += name;
        *_GP += F("</h2>\n");
    }	
    void LABEL(const char* name, const char* clas, const char* id="") {
        *_GP += F("<label class=\"");
	    *_GP += clas;
        *_GP += "\" id=\"";			
        *_GP += id;
        *_GP += F("\">");
        *_GP += name;
        *_GP += F("</label>\n");
    }
    void LABEL(String& name, const char* clas, const char* id="") {
        *_GP += F("<label class=\"");
	    *_GP += clas;
        *_GP += "\" id=\"";			
        *_GP += id;
        *_GP += F("\">");
        *_GP += name;
        *_GP += F("</label>\n");
    }	
   /* void LABEL(int name, const char* clas, const char* id="") {
        *_gp_sptr += F("<label class=\"");
	    *_gp_sptr += clas;
        *_gp_sptr += "\" id=\"";	
        *_gp_sptr += id;
        *_gp_sptr += F("\">");
        *_gp_sptr += name;
        *_gp_sptr += F("</label>\n");
    }*/
  //--------------------------------------------
  
    // ======================= КОМПОНЕНТЫ =======================
  //Изменено
	  void BUTTON(const char* name, const char* value, const char* clas) {
        *_GP += F("<input class=\"");
        *_GP += clas;
        *_GP += F("\" type=\"button\" value=\"");
        *_GP += value;
        *_GP += "\" name=\"";
        *_GP += name;
        *_GP += F("\" onclick=\"GP_click(this)\">\n");
    }
	void BUTTON(const char* name, const char* value, const char* tar, const char* clas) {
        *_GP += F("<input class=\"");
        *_GP += clas;
        *_GP += F("\" type=\"button\" value=\"");
        *_GP += value;
        *_GP += "\" name=\"";
        *_GP += name;
        *_GP += F("','");
        *_GP += tar;
        *_GP += F("')\">\n");
    }
        
        void BUTTON_LINK(const char* url, const char* value, const char* clas) {
	*_GP += F("<input class=\"");
        *_GP += clas;
        *_GP += F("<input type=\"button\" value=\"");
        *_GP += value;
        *_GP += F("\" onclick=\"location.href='");
        *_GP += url;
        *_GP += F("';\">\n");
    }
	
//----------------------------------------------------------------------------------------------------	
    //Изменено
    void NUMBER(const char* name, const char* place, const char* clas, int step, int value = INT32_MAX) {
        *_GP += F("<input class=\"");
        *_GP += clas;
        *_GP += F("\"type=\"number\" name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        if (value != INT32_MAX) {
            *_GP += F("\" value=\"");
            *_GP += value;
        }
        *_GP += F("\" placeholder=\"");
        *_GP += place;
        *_GP += F("\" step=\"");
        *_GP += step;				
        *_GP += F("\" onchange=\"GP_click(this)\">\n");
    }
	
	    void NUMBER(const char* name, const char* place, const char* clas, float value, float step) {
        *_GP += F("<input class=\"");
        *_GP += clas;
        *_GP += F("\"type=\"number\" name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" value=\"");
        *_GP += value;
        *_GP += F("\" placeholder=\"");
        *_GP += place;
        *_GP += F("\" step=\"");
        *_GP += step;		
        *_GP += F("\" onchange=\"GP_click(this)\">\n");
    }


    void AREA(const char* name, const char* clas, int rows, char* value) {
        *_GP += F("<textarea class=\"");
        *_GP += clas;
        *_GP += F("\"style=\"height:auto");
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" rows=\"");
        *_GP += rows;
        *_GP += F("\">");
        *_GP += value;
        *_GP += F("</textarea>");
    }
    void AREA(const char* name, const char* clas, int rows, String& value) {
        *_GP += F("<textarea class=\"");
        *_GP += clas;
        *_GP += F("\"style=\"height:auto");
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" rows=\"");
        *_GP += rows;
        *_GP += F("\">");
        *_GP += value;
        *_GP += F("</textarea>");
    }	
    void AREA(const char* name, const char* clas, int rows = 1) {
        *_GP += F("<textarea class=\"");
        *_GP += clas;
        *_GP += F("\"style=\"height:auto");
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" rows=\"");
        *_GP += rows;
        *_GP += F("\">");
        *_GP += F("</textarea>");
    }

 
	//--------------------------	
 //изменено
 void TEXT(const char* name, const char* place, const char* value, const char* clas) {
        *_GP += F("<input class=\"");
        *_GP += clas; 
        *_GP += F("\" type=\"text\" name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" value=\"");
        *_GP += value;
        *_GP += F("\" placeholder=\"");
        *_GP += place;
        *_GP += F("\" onchange=\"GP_click(this)\">\n");
    }
    void TEXT(const char* name, const char* place, String& value, const char* clas) {
        TEXT(name, place, (const char*)value.c_str(), clas);
    }
    void TEXT(const char* name, const char* place, char* value, const char* clas) {
        TEXT(name, place, (const char*)value, clas);
    }
    //void TEXT1(const char* name, const char* place, String& textNst, const char* clas) {
       // TEXT(name, place, (const char*)textNst.c_str(), clas);
   // }
 //изменено
 void PASS(const char* name, const char* place, const char* value, const char* clas) {
        *_GP += F("<input class=\"");
        *_GP += clas;  
        *_GP += F("\" type=\"password\" name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" value=\"");
        *_GP += value;
        *_GP += F("\" placeholder=\"");
        *_GP += place;
        *_GP += F("\" onchange=\"GP_click(this)\">\n");
    }
    void PASS(const char* name, const char* place, String& value, const char* clas) {
        PASS(name, place, (const char*)value.c_str(), clas);
    }
    void PASS(const char* name, const char* place, char* value, const char* clas) {
        PASS(name, place, (const char*)value, clas);
    }
    void CHECK(const char* name, bool x = 0) {
        *_GP += F("<input type=\"checkbox\" name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += (x ? F("\" checked") : F("\""));
        *_GP += F(" onclick=\"GP_click(this)\">\n");
    }
    void SWITCH(const char* name, bool x = 0) {
        *_GP += F("<label class=\"switch\"><input type=\"checkbox\" name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += (x ? F("\" checked") : F("\""));
        *_GP += F(" onclick=\"GP_click(this)\">\n");
        *_GP += F("<span class=\"slider\"></span></label>");
    }
     void DATE(const char* name) {
        *_GP += F("<input type=\"date\" name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" onchange=\"GP_click(this)\">\n");
    }
    void DATE(const char* name, GPdate d) {
        *_GP += F("<input type=\"date\" name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" value=\"");
        _GP->reserve(_GP->length() + 11);
        *_GP += d.encode();
        *_GP += F("\" onchange=\"GP_click(this)\">\n");
    }
    
    void TIME(const char* name) {
        *_GP += F("<input type=\"time\" name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" onchange=\"GP_click(this)\">\n");
    }
    void TIME(const char* name, GPtime t) {
        *_GP += F("<input type=\"time\" name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" value=\"");
        _GP->reserve(_GP->length() + 8);
        *_GP += t.encode();
        *_GP += F("\" onchange=\"GP_click(this)\">\n");
    }
    void LABEL_MINI(int text) {
        *_GP += F("<label class=\"sldLbl\">");
        *_GP += text;
        *_GP += F("</label>");
    }
    void SLIDER(const char* name, int value, int min, int max, int step = 1) {
		  // Вставка
		*_GP += F("<label class=\"sldLblValue\" id=\"");
        *_GP += name;
        *_GP += F("_value\">");
        *_GP += value;
        *_GP += F("</label>");
		    // Конец вставки
        LABEL_MINI(min);
        *_GP += F("<input type=\"range\" name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" value=\"");
        *_GP += value;
        *_GP += F("\" min=\"");
        *_GP += min;
        *_GP += F("\" max=\"");
        *_GP += max;
        *_GP += F("\" step=\"");
        *_GP += step;
        //Модифицировано
        *_GP += F("\" oninput=\"GP_click(this);document.getElementById('");
        *_GP += name;
        *_GP += F("_value').innerHTML=this.value;\">\n");
       //Конец модификации
        LABEL_MINI(max);
    }

void SLIDER(const char* name, const char* label, int value, int min, int max, int step = 1) {
     *_GP += F("<div class=\"sldBlock\">");
     *_GP += F("<label>");
     *_GP += label;
     *_GP += F("</label>");
     SLIDER(name, value, min, max, step);
     *_GP += F("</div>");
    }
    void COLOR(const char* name, uint32_t value = 0) {
        *_GP += F("<input type=\"color\" name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" value=\"");
        *_GP += encodeColor(value);
        *_GP += F("\" onchange=\"GP_click(this)\">\n");
    }

    void SELECT1(const char* name, const char* valuesst, int8_t sel = 0) {
        if (sel < 0) sel = 0;
        *_GP += F("<select name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" onchange=\"GP_click(this)\">\n");
        char buf[strlen(valuesst) + 1];
        strcpy(buf, valuesst);
        char* str = buf;
        uint8_t count = 0;
        splitList(NULL);
        while ((str = splitList(buf)) != NULL) {
            *_GP += F("<option value=\"");
            *_GP += str;
            *_GP += F("\"");
            if (count++ == sel) *_GP += F("selected");
            *_GP += F(">");
            *_GP += str;
            *_GP += F("</option>\n");
        }
        *_GP += F("</select>");
    }
    void SELECT(const char* name, const char* values, int8_t sel = 0) {
        
         if (sel < 0) sel = 0;
        *_GP += F("<select name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\" onchange=\"GP_click(this)\">\n");
        char buf[strlen(values) + 1];
        strcpy(buf, values);
        char* str = buf;
        uint8_t count = 0;
        splitList(NULL);
        while ((str = splitList(buf)) != NULL) {
            *_GP += F("<option value=\"");
            *_GP += str;
            *_GP += F("\"");
            if (count++ == sel) *_GP += F("selected");
            *_GP += F(">");
            *_GP += str;
            *_GP += F("</option>\n");
        }
        *_GP += F("</select>");
    }
    void LED_RED(const char* name, bool state = 0) {
        *_GP += F("<input class=\"led red\" type=\"radio\" disabled ");
        if (state) *_GP += F("checked ");
        *_GP += F("name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\">");
    }
    void LED_GREEN(const char* name, bool state = 0) {
        *_GP += F("<input class=\"led green\" type=\"radio\" disabled ");
        if (state) *_GP += F("checked ");
        *_GP += F("name=\"");
        *_GP += name;
        *_GP += F("\" id=\"");
        *_GP += name;
        *_GP += F("\">");
    }
	void IMAGE(const char* name) {
        *_GP += F("<img src=\"");
        *_GP += name;
        *_GP += F("\">");
    }
    
    // ======================= ГРАФИКИ =======================
    template <uint8_t ax, uint8_t am>
    void PLOT(const char* id, const char** labels, int16_t vals[ax][am], int dec = 0) {
        *_GP += F("<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>\n"
        "<script type=\"text/javascript\">\n"
        "google.charts.load('current', {'packages':['corechart']});\n"
        "google.charts.setOnLoadCallback(drawChart);\n"
        "function drawChart() {\n"
        "var data = google.visualization.arrayToDataTable([\n");
        
        *_GP += '[';
        for (int i = 0; i < ax+1; i++) {
            *_GP += '\'';
            if (i) *_GP += labels[i-1];
            *_GP += "',";
        }
        *_GP += "],\n";
        for (int j = 0; j < am; j++) {
            *_GP += '[';
            for (int i = 0; i < ax+1; i++) {
                if (!i) *_GP += '\'';
                if (!i) *_GP += j;
                else {
                    if (dec) *_GP += (float)vals[i-1][j] / dec;
                    else *_GP += vals[i-1][j];
                }
                if (!i) *_GP += '\'';
                *_GP += ',';
            }
            *_GP += F("],\n");
        }
        
        *_GP += F("]);var options = {pointSize:5,curveType:'function','chartArea':{'width':'90%','height':'90%'},\n"
        "backgroundColor:'none',hAxis:{title:''},vAxis:{title:''},\n"
        "legend: {position:'bottom'}};\n"
        "var chart = new google.visualization.LineChart(document.getElementById('");
        *_GP += id;
        *_GP += F("'));\n");
        *_GP += F("chart.draw(data, options);}\n"
        "</script><div id=\"");
        *_GP += id;
        *_GP += F("\" class=\"chartBlock\"></div>\n");
    }
    
    template <uint8_t ax, uint8_t am>
    void PLOT_DARK(const char* id, const char** labels, int16_t vals[ax][am], int dec = 0) {
        *_GP += F("<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>\n"
        "<script type=\"text/javascript\">\n"
        "google.charts.load('current', {'packages':['corechart']});\n"
        "google.charts.setOnLoadCallback(drawChart);\n"
        "function drawChart() {\n"
        "var data = google.visualization.arrayToDataTable([\n");
        
        *_GP += '[';
        for (int i = 0; i < ax+1; i++) {
            *_GP += '\'';
            if (i) *_GP += labels[i-1];
            *_GP += "',";
        }
        *_GP += "],\n";
        for (int j = 0; j < am; j++) {
            *_GP += '[';
            for (int i = 0; i < ax+1; i++) {
                if (!i) *_GP += '\'';
                if (!i) *_GP += j;
                else {
                    if (dec) *_GP += (float)vals[i-1][j] / dec;
                    else *_GP += vals[i-1][j];
                }
                if (!i) *_GP += '\'';
                *_GP += ',';
            }
            *_GP += F("],\n");
        }
        
        *_GP += F("]);var options = {pointSize:5,curveType:'function','chartArea':{'width':'90%','height':'90%'},\n"
        "backgroundColor:'none',hAxis:{title:'',titleTextStyle:{color:'#ddd'},textStyle:{color:'#bbb'}},\n"
        "vAxis:{title:'',titleTextStyle:{color:'#ddd'},gridlines:{color:'#777'},textStyle:{color:'#bbb'}},\n"
        "legend: {position:'bottom',textStyle:{color:'#eee'}}};\n"
        "var chart = new google.visualization.LineChart(document.getElementById('");
        *_GP += id;
        *_GP += F("'));\n");
        *_GP += F("chart.draw(data, options);}\n");
        *_GP += F("</script><div id=\"");
        *_GP += id;
        *_GP += F("\" class=\"chartBlock\"></div>\n");
    }
    
    void AJAX_PLOT(const char* name, int axes, int xamount = 20, int prd = 1000) {
        *_GP += F(""
        "<script src=\"https://code.highcharts.com/highcharts.js\"></script>\n"
        "<div id=\"");
        *_GP += name;
        *_GP += F("\" class=\"chartBlock\"></div><script>\n"
        "var ");
        *_GP += name;
        *_GP += F("=new Highcharts.Chart({\n"
        "chart:{borderRadius:10,renderTo:'");
        *_GP += name;
        *_GP += F("',style:{fontFamily:\"sans-serif\"}},\n"
        "title:{text:''},"
        "series:[");
        for (int i = 0; i < axes; i++) {
            *_GP += F("{data:[]}");
            if (i != axes - 1) *_GP += ',';
        }
        *_GP += F("],\n"
        "xAxis:{type:'datetime',dateTimeLabelFormats:{second:'%H:%M:%S'}},\n"
        "yAxis:{title:{enabled:false}},"
        "credits:{enabled:false}});\n"
        "setInterval(function(){var xhttp=new XMLHttpRequest();var ch=");
        *_GP += name;
        *_GP += F("\n"
        "xhttp.onreadystatechange=function(){if(this.readyState==4&&this.status==200){\n"
        "var x=(new Date()).getTime();"
        "var arr=this.responseText.split(',');"
        "var move=(ch.series[0].data.length>");
        *_GP += xamount;
        *_GP += F(");\n"
        "for(let i=0;i<arr.length;i++)ch.series[i].addPoint([x,Number(arr[i])],true,move,true);\n"
        "}};xhttp.open(\"GET\",\"GP_update?");
        *_GP += name;
        *_GP += F("\",true);xhttp.send();},\n");
        *_GP += prd;
        *_GP += F(");</script>\n");
    }
    
    void AJAX_PLOT_DARK(const char* name, int axes, int xamount = 20, int prd = 1000) {
        *_GP += F(""
        "<script src=\"https://code.highcharts.com/highcharts.js\"></script>\n"
        "<script src=\"https://code.highcharts.com/themes/dark-unica.js\"></script>\n"
        "<div id=\"");
        *_GP += name;
        *_GP += F("\" class=\"chartBlock\"></div><script>\n"
        "var ");
        *_GP += name;
        *_GP += F("=new Highcharts.Chart({\n"
        "chart:{borderRadius:10,renderTo:'");
        *_GP += name;
        *_GP += F("',style:{fontFamily:\"sans-serif\"}},\n"
        "title:{text:''},"
        "series:[");
        for (int i = 0; i < axes; i++) {
            *_GP += F("{data:[]}");
            if (i != axes - 1) *_GP += ',';
        }
        *_GP += F("],\n"
        "xAxis:{type:'datetime',dateTimeLabelFormats:{second:'%H:%M:%S'}},\n"
        "yAxis:{title:{enabled:false}},"
        "credits:{enabled:false}});\n"
        "setInterval(function(){var xhttp=new XMLHttpRequest();var ch=");
        *_GP += name;
        *_GP += F("\n"
        "xhttp.onreadystatechange=function(){if(this.readyState==4&&this.status==200){\n"
        "var x=(new Date()).getTime();"
        "var arr=this.responseText.split(',');"
        "var move=(ch.series[0].data.length>");
        *_GP += xamount;
        *_GP += F(");\n"
        "for(let i=0;i<arr.length;i++)ch.series[i].addPoint([x,Number(arr[i])],true,move,true);\n"
        "}};xhttp.open(\"GET\",\"GP_update?");
        *_GP += name;
        *_GP += F("\",true);xhttp.send();},\n");
        *_GP += prd;
        *_GP += F(");</script>\n");
    }
    
    template <uint8_t ax, uint8_t am>
    void PLOT_STOCK(const char* id, const char** labels, uint32_t* times, int16_t vals[ax][am], int dec = 0) {
        *_GP += F("<script src=\"https://code.highcharts.com/stock/highstock.js\"></script>\n"
        "<div class=\"chartBlock\" id=\"");
        *_GP += id;
        *_GP += F("\"></div>");
        *_GP += F("<script>Highcharts.stockChart('");
        *_GP += id;
        *_GP += F("',{chart:{},\n"
        "rangeSelector:{buttons:[\n"
        "{count:1,type:'minute',text:'1M'},\n"
        "{count:1,type:'hour',text:'1H'},\n"
        "{count:1,type:'day',text:'1D'},\n"
        "{type:'all',text:'All'}],\n"
        "inputEnabled:false,selected:0},\n"
        "time:{useUTC:false},\n"
        "credits:{enabled:false},series:[\n");
        for (int axs = 0; axs < ax; axs++) {
            *_GP += F("{name:'");
            *_GP += labels[axs];
            *_GP += F("',data:[\n");
            for (int ams = 0; ams < am; ams++) {
                *_GP += '[';
                *_GP += times[ams];
                *_GP += F("000");
                *_GP += ',';
                if (dec) *_GP += (float)vals[axs][ams] / dec;
                else *_GP += vals[axs][ams];
                *_GP += "],\n";
            }
            *_GP += "]},\n";
        }
        *_GP += F("]});</script>\n");
    }
    
    template <uint8_t ax, uint8_t am>
    void PLOT_STOCK_DARK(const char* id, const char** labels, uint32_t* times, int16_t vals[ax][am], int dec = 0) {
        *_GP += F("<script src=\"https://code.highcharts.com/stock/highstock.js\"></script>\n"
        "<script src=\"https://code.highcharts.com/themes/dark-unica.js\"></script>"
        "<div class=\"chartBlock\" id=\"");
        *_GP += id;
        *_GP += F("\"></div>");
        *_GP += F("<script>Highcharts.stockChart('");
        *_GP += id;
        *_GP += F("',{chart:{},\n"
        "rangeSelector:{buttons:[\n"
        "{count:1,type:'minute',text:'1M'},\n"
        "{count:1,type:'hour',text:'1H'},\n"
        "{count:1,type:'day',text:'1D'},\n"
        "{type:'all',text:'All'}],\n"
        "inputEnabled:false,selected:0},\n"
        "time:{useUTC:false},\n"
        "credits:{enabled:false},series:[\n");
        for (int axs = 0; axs < ax; axs++) {
            *_GP += F("{name:'");
            *_GP += labels[axs];
            *_GP += F("',data:[\n");
            for (int ams = 0; ams < am; ams++) {
                *_GP += '[';
                *_GP += times[ams];
                *_GP += F("000");
                *_GP += ',';
                if (dec) *_GP += (float)vals[axs][ams] / dec;
                else *_GP += vals[axs][ams];
                *_GP += "],\n";
            }
            *_GP += "]},\n";
        }
        *_GP += F("]});</script>\n");
    }
};

extern Builder add;
extern Builder GP;

// ======================= БИЛДЕР =======================
// собирать страницу
void BUILD_BEGIN();

// завершить сборку
void BUILD_END();

// ===================== DEPRECATED =====================
void GP_BUILD(__attribute__((unused)) String& s);
void BUILD_BEGIN(__attribute__((unused)) String& s);
void GP_SHOW();
#endif