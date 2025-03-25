#ifndef __SETTING_H__
#define __SETTING_H__

#define RANDOM 1
#define MEDIAN 2
#define CHAR_SIZE 10

#include <fstream>
using namespace std;

int getLines() {
    int len = 0;
    ofstream file("./daegu_weather_2024_output.txt");


    file.close();
    return len;
}

#endif