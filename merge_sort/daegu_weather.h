#ifndef __DAEGU_WEATHER_H__
#define __DAEGU_WEATHER_H__

#include "setting.h"
#include <string>
#include <cstring>
using namespace std;

typedef struct DaeguWeather{
    char date[MAX_CHAR_SIZE];
    int temperature;
} DaeguWeather;

int setWeathers(DaeguWeather** weathers, DaeguWeather** result);
void mergeSortWeather(DaeguWeather* weathers, DaeguWeather* result, int p, int q);
void mergeWeather(DaeguWeather weathers, DaeguWeather* result, int p, int q);
void printWeather(DaeguWeather* weathers);
void copyResultToList(DaeguWeather* weathers, DaeguWeather* result, int p, int q);
void test(DaeguWeather* weathers);
void printTop3(DaeguWeather* weathers);
DaeguWeather* makeNewDaeguWeather(string line);
void saveWeather(DaeguWeather* weathers);

#endif