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
    DaeguWeather *result;

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
};

// {6, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2}
// {6, 3, 11, 9,  12, 2, 8, 15, 18, 10, 7, 14}
QuickSortWeather::QuickSortWeather(int len) {
    this->len = len;
    count = 0;
    arr = new DaeguWeather[len];
    result = new DaeguWeather[len];
}

QuickSortWeather::~QuickSortWeather() {
    delete []arr;
    delete []result;
}

// [p, q] => 피벗선정
// 피벗의 왼쪽에 피봇보다 큰값이 오른쪽엔 작은값이 와야된다.
void QuickSortWeather::exec2WayPartitioning(int p, int q, int type){
    if((q - p) <= 1) {
        if(arr[p].temp > arr[q].temp && (q-p) == 1) {
            exchange(p, q);
            return;
        }
        return;
    }

    // 피봇 선정
    int newPivotIdx = ((type == RANDOM) ? selectRandomPivot(p, q) : selectMedianPivot(p, q));
    if(p < q) {
        exchange(p, newPivotIdx);
        newPivotIdx = p;
        count++;
        
        int leftIdx = p + 1;
        int rightIdx = type == RANDOM ? q : q - 1;
        int lastChangeLeftIdx = p + 1; 
        while(true) {
            while(arr[newPivotIdx].temp > arr[leftIdx].temp && leftIdx < rightIdx) leftIdx++;
            while(arr[newPivotIdx].temp < arr[rightIdx].temp && leftIdx < rightIdx) rightIdx--;
            if(leftIdx < rightIdx) {
                exchange(leftIdx, rightIdx);
                lastChangeLeftIdx = leftIdx;
                leftIdx++; rightIdx--;
            }

            // 반복문 종료 조건은 왼쪽 포인터가 오른쪽 포인터와 겹치거나 앞서갈때 멈춘다.
            if(leftIdx >= rightIdx) {
                // 탐색하지 못한 경우, 피봇이랑 교체할 가장 작은 값을 찾아야된다.
                // 중요한 건 결국 피벗을 기준으로 왼쪽엔 피봇보다 작은값, 오른쪽엔 큰값이 배치되어야 한다.
                if(rightIdx == leftIdx) {
                    int min = lastChangeLeftIdx;
                    for(int i = lastChangeLeftIdx; i <= leftIdx; i++){
                        if(arr[i].temp < arr[newPivotIdx].temp) min = i;
                    }
                    if(arr[newPivotIdx].temp < arr[min].temp) break;  
                    exchange(min, newPivotIdx);
                    newPivotIdx = min;
                }
                else {
                    exchange(lastChangeLeftIdx, newPivotIdx);
                    newPivotIdx = lastChangeLeftIdx;
                }
                break;
            }
        }
        exec2WayPartitioning(p, newPivotIdx - 1, type);
        exec2WayPartitioning(newPivotIdx + 1, q, type);
    }
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
    srand(time(NULL));
    int random =rand() % (q - p + 1) + p; 
    count++;
    return random;
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
    cout << "[MEDIAN] start : " << result[start].temp << "/ middle : " << result[middle].temp << "/ end : " << result[end].temp << endl;
    count++;
    return middle;
}

void QuickSortWeather::printResult() {
    cout << "[PRINT START]";
    for(int i = 0; i < len; i++) {
        if( i % 7 == 0) cout << endl;
        cout << "[" << result[i].date << "|" << result[i].temp << "]" << " -> " ;
    }
    cout << "[END]" << endl;
    cout << "[PIVOT COUNT] : " << count << endl;
}

void QuickSortWeather::exchange(int p, int q) {
    DaeguWeather temp = arr[p];
    arr[p] = arr[q];
    arr[q] = temp;
}

// void QuickSortWeather::saveFile() {
//     ifstream file("./daegu_weather_2024_output.txt");
//     file.close();
// }

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
        result[i] = *weather;
        i++;
    }
    file.close();
}

int QuickSortWeather::getCount() {
    return this->count;
}

#endif