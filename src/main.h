#pragma once

#include "Arduino.h"
#include <GyverNTP.h>
#include <DFRobotDFPlayerMini.h>
#include <MD_Parola.h>
#include <GyverPortal.h>
#include <iarduino_RTC.h>

// display
extern MD_Parola parola;

extern GyverNTP ntp;

extern DFRobotDFPlayerMini dfPlayer;
extern int dfp_volume;

extern GyverPortal portal;
extern iarduino_RTC watch;

// какие-то флаги
extern bool printCom, modeeff, flagzapros;
//будильник
extern bool flagBudilnik;
//extern bool BUD,BUD1,BUD2,BUD3,BUD4,BUD5,BUD6,BUD7;
//extern int hBud,hBud1,hBud2,hBud3,hBud4,hBud5,hBud6,hBud7;
//extern int mBud,mBud1,mBud2,mBud3,mBud4,mBud5,mBud6,mBud7;

// Погода
extern int location_code;

// parola vars
extern textPosition_t just;
// flags
extern bool flagValute, flagToch;

// buffers
extern String textStringBuff1;
extern char dateStringBuff[70];
extern char Buf[20];
extern char home_sens_buff[250];
extern char aforizm_buff[500];
extern char BufVal[250];


// sensors
extern int wett, wetp, weth;
extern bool M1, M2, M3, M4, M5;
extern int CorTemp;     // коррекция температуры
extern int  corrPress;  // коррекция давления
extern int CorHum;      // коррекция влажности
void start_sensors();


// night mode On/Off time
extern int hNon, mNon, sNon, hNoff, mNoff, sNoff;

// непонятные переменные
extern int sk, unknown_q, yar, oldyar, chrift, MG, Pn;
extern uint8_t modDate;
extern bool swtRTC, someNightModeVar;

//будильник
extern bool BUD,BUD1,BUD2,BUD3,BUD4,BUD5,BUD6,BUD7;
extern int hBud,hBud1,hBud2,hBud3,hBud4,hBud5,hBud6,hBud7;
extern int mBud,mBud1,mBud2,mBud3,mBud4,mBud5,mBud6,mBud7;
extern int Pap,PaB1,PaB2,PaB3,PaB4,PaB5,PaB6,PaB7;

// statics
static constexpr std::array<const char*, 8> weekDay = {"", "понедельник", "вторник", "среда", "четверг", "пятница", "суббота", "воскресенье"};
static constexpr std::array<const char*, 13> months = {"","января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря"};


void Mod1();
void Mod2();
void Mod5();
void Mod7();


bool loadConfig();
bool saveConfig();

void mkTime();
void gv_portal_run();
void gv_portal_build();
void loginPortal();
void wifiReconect();
void getSens();
