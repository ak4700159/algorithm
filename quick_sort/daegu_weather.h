#ifndef __DAEGU_WEATHER_H__
#define __DAEGU_WEATHER_H__

#include <cstring>
#include <iostream>
using namespace std;

class DaeguWeather{
public:
    int temp;
    char* date;
public:
    DaeguWeather(int temp, char* date) {
        this->temp = temp;
        strcpy(this->date, date);
    }

    void print() {
        cout << "[temp:" << temp << "]/[" << date << "]";
    }
};

#endif