#include "setting.h"
#include "merge.h"
#include "daegu_weather.h"
#include <iostream>
#include <fstream>

using namespace std;

void solutionOne();
void solutionTwo();

int main() {
    cout << "solution one start : " << endl;
    solutionOne();
    cout << "-----------------------------------" << endl;
    cout << "solution two start : " << endl;
    solutionTwo();
    return 0;
}

void solutionOne() {
    int list[MAX_LIST_SIZE] = {37, 10, 22, 30, 35, 13, 25, 24};
    int result[MAX_LIST_SIZE] = { 0 };
    int listLen = sizeof(list) / 4;
    int resultLen = sizeof(result) / 4;

    printList(list, resultLen);
    merge_sort(list, result, 0, listLen - 1);
    printList(result, resultLen);
}

void solutionTwo() {
    DaeguWeather** weathers = (DaeguWeather**)malloc(sizeof(DaeguWeather*));
    DaeguWeather** result = (DaeguWeather**)malloc(sizeof(DaeguWeather*));
    int len = setWeathers(weathers, result);
    mergeSortWeather(weathers[0], result[0], 0, len-1);
    printTop3(result[0]);
    saveWeather(result[0]);
}
