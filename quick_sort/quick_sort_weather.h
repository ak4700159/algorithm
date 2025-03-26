#ifndef __QUICK_WEATHER_H__
#define __QUICK_WEATHER_H__

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <istream>
#include <string>
#include "setting.h"
#include "daegu_weather.h"
using namespace std;

class QuickSortWeather{
private:
    // 피봇 선택 카운터
    int count;
    int len;
    DaeguWeather *arr;

public:
    QuickSortWeather(int);
    ~QuickSortWeather();
    void exchange(int, int);
    void exec2WayPartitioning(int, int, int);
    void exec3WayPartitioning(int, int);

    int selectRandomPivot(int, int);
    int selectMedianPivot(int, int);
    void printResult();
    void readFile();
    void saveFile();
    int getCount();
    void initCount();
};

// {6, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2}
// {6, 3, 11, 9,  12, 2, 8, 15, 18, 10, 7, 14}
QuickSortWeather::QuickSortWeather(int len) {
    this->len = len;
    count = 0;
    arr = new DaeguWeather[len];
}

QuickSortWeather::~QuickSortWeather() {
    delete []arr;
}

// [p, q] => 피벗선정
// 피벗의 왼쪽에 피봇보다 큰값이 오른쪽엔 작은값이 와야된다.
void QuickSortWeather::exec2WayPartitioning(int p, int q, int type){
    if (p >= q) return;

    int pivotIdx;
    switch(type) {
        case RANDOM: pivotIdx = selectRandomPivot(p, q); break;
        case MID: pivotIdx = (p + q) / 2; break;
        case MEDIAN: pivotIdx = selectMedianPivot(p, q); break;
    }

    exchange(p, pivotIdx);
    int pivotValue = arr[p].temp;
    // i = left index;
    int i = p + 1;
    // j = right index;
    int j = type == MEDIAN ? q - 1 : q;

    while (i <= j) {
        while (i <= q && arr[i].temp <= pivotValue) i++;
        while (j > p && arr[j].temp > pivotValue) j--;
        if (i < j) {
            exchange(i, j);
        }
    }

    exchange(p, j); // 피봇 위치 복원
    exec2WayPartitioning(p, j - 1, type);
    exec2WayPartitioning(j + 1, q, type);
}

void QuickSortWeather::exec3WayPartitioning(int p, int q){
    if((q - p) <= 1) {
        if(arr[p].temp > arr[q].temp && (q-p) == 1) {
            exchange(p, q);
            return;
        }
        return;
    }

    int pivotValue = arr[p].temp;
    int leftDuplicatedIdx = p;
    int rightDuplicatedIdx = q;
    int i = p;
    count++;
    while(i <= rightDuplicatedIdx) {
        if (arr[i].temp < pivotValue) {
            exchange(i, leftDuplicatedIdx);
            leftDuplicatedIdx++;
            i++;
        } else if (arr[i].temp > pivotValue) {
            exchange(i, rightDuplicatedIdx);
            rightDuplicatedIdx--;
        } else {
            i++;
        }
    }
    exec3WayPartitioning(p, leftDuplicatedIdx - 1);
    exec3WayPartitioning(rightDuplicatedIdx + 1, q);
}

int QuickSortWeather::selectRandomPivot(int p, int q){
    srand(time(NULL) + p + q);
    int pivot;
    pivot = rand() % (q - p + 1) + p;
    count++;
    return pivot;
}

// 최소 요소가 3개 이상일 때 실행된다.
int QuickSortWeather::selectMedianPivot(int p, int q){
    int start = p;
    int middle = (p + q) / 2;
    int end = q;
    // 3개 요소에 대해 정렬
    if(arr[start].temp > arr[middle].temp){
        exchange(start, middle);
        if(arr[middle].temp > arr[end].temp){
            exchange(middle, end);
            if(arr[start].temp > arr[middle].temp){
                exchange(start, middle);
            }
        }
    }
    else if(arr[start].temp > arr[end].temp) {
        exchange(start, end);
        if(arr[middle].temp > arr[end].temp) {
            exchange(middle, end);
        }
    } else if(arr[middle].temp > arr[end].temp) {
        exchange(middle, end);
    }
    // cout << "[MEDIAN] start : " << arr[start].temp << "/ middle : " << arr[middle].temp << "/ end : " << arr[end].temp << endl;
    count++;
    return middle;
}

void QuickSortWeather::printResult() {
    // cout << "[PRINT START]";
    // for(int i = 0; i < len; i++) {
    //     if( i % 7 == 0) cout << endl;
    //     cout << "[" << arr[i].date << "|" << arr[i].temp << "]" << " -> " ;
    // }
    // cout << "[END]" << endl;
    cout << "[PIVOT COUNT] : " << count << endl;
}

void QuickSortWeather::exchange(int p, int q) {
    DaeguWeather temp = arr[p];
    arr[p] = arr[q];
    arr[q] = temp;
}

void QuickSortWeather::readFile() {
    ifstream file; file.open("./daegu_weather_2024.txt");
    string line;
    int i = 0;
    while (getline(file, line)){
        string date = line.substr(0, sizeof("0000-00-00") - 1);
        int temp = stoi(line.substr(line.find(" ")));
        DaeguWeather* weather = new DaeguWeather();
        weather->temp = temp;
        strcpy(weather->date, date.c_str());
        arr[i] = *weather;
        i++;
    }
    file.close();
}

int QuickSortWeather::getCount() {
    return this->count;
}

void QuickSortWeather::initCount() {
    this->count = 0;
}

#endif