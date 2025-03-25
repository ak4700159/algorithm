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
    char* date;
public:
    DaeguWeather() {}
    DaeguWeather(int temp, char* date) {
        this->temp = temp;
        strcpy(this->date, date);
    }

    char* toString() {
        char buf[CHAR_SIZE];
        sprintf("[temp:%d]/[date:%s]", buf, temp, date);
        return buf;
    }
};

#endif