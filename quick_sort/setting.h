#ifndef __SETTING_H__
#define __SETTING_H__

#define RANDOM 1
#define MEDIAN 2
#define MID 3
#define CHAR_SIZE 10

#include <fstream>
using namespace std;

int getLines() {
    int len = 0;
    ifstream file("./daegu_weather_2024.txt");
    string line;
    while (getline(file, line)) len++;
    file.close();
    return len;
}

#endif