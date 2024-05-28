#include "Arduino.h"
#include "utils.h"

String* _GP = nullptr;

String encodeDate(GPdate d) {
    return d.encode();
}
String encodeTime(GPtime t) {
    return t.encode();
}
String encodeColor(GPcolor c) {
    return c.encode();
}

uint32_t GPunix(uint16_t y, uint8_t m, uint8_t d, uint8_t h, uint8_t mn, uint8_t s, int8_t gmt) {
    int8_t my = (m >= 3) ? 1 : 0;
    y += my - 1970;
    uint16_t dm = 0;
    for (int i = 0; i < m - 1; i++) dm += (i<7)?((i==1)?28:((i&1)?30:31)):((i&1)?31:30);
    return (((d-1+dm+((y+1)>>2)-((y+69)/100)+((y+369)/100/4)+365*(y-my))*24ul+h-gmt)*60ul+mn)*60ul+s;
}

void GPaddInt(int16_t val, int16_t* arr, uint8_t am) {
    for (int i = 0; i < am - 1; i++) arr[i] = arr[i + 1];
    arr[am - 1] = val;
}
void GPaddUnix(uint32_t val, uint32_t* arr, uint8_t am) {
    for (int i = 0; i < am - 1; i++) arr[i] = arr[i + 1];
    arr[am - 1] = val;
}
void GPaddUnixS(int16_t val, uint32_t* arr, uint8_t am) {
    for (int i = 0; i < am - 1; i++) arr[i] = arr[i + 1];
    arr[am - 1] += val;
}

char* splitList(char* str) {
    static uint8_t prev, end;
    if (str == NULL) prev = end = 0;
    else {
        if (prev) *(str + prev - 1) = ',';
        char* cur = strchr(str+prev, ',');
        if (cur) {
            *cur = '\0';
            uint8_t b = prev;
            prev = cur - str + 1;
            return str + b;
        } else if (!end) {
            end = 1;
            return str + prev;
        }
    }
    return NULL;
}

// получить номер, под которым name входит в list (вида "val1,val2,val3")
int8_t inList(const char* name, const char* list) {
    char buf[strlen(list) + 1];
    strcpy(buf, list);
    char* str = buf;
    int8_t count = 0, pos = -1;
    splitList(NULL);
    while ((str = splitList((char*)buf)) != NULL) {
        if (!strcmp(str, name)) pos = count;
        count++;
    }
    return pos;
}

int8_t inList(String& s, const char* list) {
    return inList(s.c_str(), list);
}

int8_t inList(const String& s, const char* list) {
    return inList(s.c_str(), list);
}