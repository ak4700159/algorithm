#ifndef __DAEGU_WEATHER_H__
#define __DAEGU_WEATHER_H__

#include "setting.h"
#include <string>
using namespace std;

typedef struct DaeguWeather{
    string date;
    int temperature;
} DaeguWeather;

int setWeathers(DaeguWeather weathers[]);
void weatherMergeSort(DaeguWeather weathers[], DaeguWeather result[], int len);
void weatherMerge(DaeguWeather weathers[], DaeguWeather result[], int p, int q, int k);
void mergeSort(DaeguWeather weathers[], DaeguWeather result[], int p, int q);
void printList(DaeguWeather weathers[], int len);
void copyResultToList(DaeguWeather weathers[], DaeguWeather result[], int p, int q);

#endif