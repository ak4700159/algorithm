#include "setting.h"
#include "merge.h"
#include "daegu_weather.h"

#include <iostream>
#include <fstream>

using namespace std;

void solution1();
void solution2();

int main() {
    solution1();
    solution2();
    return 0;
}

void solution1() {
    int list[MAX_LIST_SIZE] = {37, 10, 22, 30, 35, 13, 25, 24};
    int result[MAX_LIST_SIZE] = { 0 };
    int listLen = sizeof(list) / 4;
    int resultLen = sizeof(result) / 4;

    printList(list, resultLen);
    merge_sort(list, result, 0, listLen - 1);
    printList(result, resultLen);
}

void solution2() {
    DaeguWeather* weathers;
    int len = setWeathers(weathers) - 1;
    printList(weathers, len);
}

