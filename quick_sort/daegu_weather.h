#ifndef __DAEGU_WEATHER_H__
#define __DAEGU_WEATHER_H__

#include <cstring>
#include <iostream>
#include <cstdio>
#include "setting.h"
using namespace std;

class DaeguWeather{
public:
    int temp;
    char date[CHAR_SIZE];
public:
    DaeguWeather() {}
    DaeguWeather(int temp, char* date) {
        this->temp = temp;
        strcpy(this->date, date);
    }

    char* toString() {
        char buf[CHAR_SIZE];
        sprintf(buf, "[temp:%d]/[date:%s]", temp, date);

        char* buf2;
        strcpy(buf2, buf);
        return buf2;
    }
};

#endif 