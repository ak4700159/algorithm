#ifndef __QUICK_INT_H__
#define __QUICK_INT_H__

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "setting.h"
using namespace std;

class QuickSortInt{
private:
    // 피봇 선택 카운터
    int count;
    int len;
    int *arr;
    int *result;

public:
    QuickSortInt(int);
    ~QuickSortInt();
    void exchange(int, int);
    void exec2WayPartitioning(int, int, int);
    void exec3WayPartitioning(int, int);

    int selectRandomPivot(int, int);
    int selectMedianPivot(int, int);
    void printResult();
    void readFile();
};

// {6, 2, 2, 2,  6, 6, 2, 2, 2, 2, 2, 2}
// {6, 3, 11, 9,  12, 2, 8, 15, 18, 10, 7, 14}
QuickSortInt::QuickSortInt(int len) {
    this->len = len;
    count = 0;
    arr = new int[len] {6, 3, 11, 9,  12, 2, 8, 15, 18, 10, 7, 14};
    result = new int[len] {6, 3, 11, 9,  12, 2, 8, 15, 18, 10, 7, 14};
}

QuickSortInt::~QuickSortInt() {
    delete []arr;
    delete []result;
}

// [p, q] => 피벗선정
// 피벗의 왼쪽에 피봇보다 큰값이 오른쪽엔 작은값이 와야된다.
void QuickSortInt::exec2WayPartitioning(int p, int q, int type){
    if (p >= q) return;

    int pivotIdx;
    switch(type) {
        case RANDOM: pivotIdx = selectRandomPivot(p, q); break;
        case MID: pivotIdx = (p + q) / 2; break;
        case MEDIAN: pivotIdx = selectMedianPivot(p, q); break;
    }

    // 맨 앞에 있는 요소와 피벗을 교환
    exchange(p, pivotIdx);
    int pivotValue = arr[p];
    // i = left index;
    int i = p + 1;
    // j = right index;
    int j = type == MEDIAN ? q - 1 : q;

    while (i <= j) {
        while (i <= q && arr[i] <= pivotValue) i++;
        while (j > p && arr[j] > pivotValue) j--;
        if (i < j) {
            exchange(i, j);
        }
    }

    exchange(p, j); // 피봇 위치 복원
    count++;
    // printResult();

    exec2WayPartitioning(p, j - 1, type);
    exec2WayPartitioning(j + 1, q, type);
}

void QuickSortInt::exec3WayPartitioning(int p, int q){
    if (p >= q) return;

    int pivotValue = arr[p];
    int leftDuplicatedIdx = p;
    int rightDuplicatedIdx = q;
    int i = p;
    count++;
    while(i <= rightDuplicatedIdx) {
        if (arr[i] < pivotValue) {
            exchange(i, leftDuplicatedIdx);
            leftDuplicatedIdx++;
            i++;
        } else if (arr[i] > pivotValue) {
            exchange(i, rightDuplicatedIdx);
            rightDuplicatedIdx--;
        } else {
            i++;
        }
    }
    exec3WayPartitioning(p, leftDuplicatedIdx - 1);
    exec3WayPartitioning(rightDuplicatedIdx + 1, q);
}

int QuickSortInt::selectRandomPivot(int p, int q){
    srand(time(NULL));
    int random =rand() % (q - p + 1) + p; 
    count++;
    return random;
}

// 최소 요소가 3개 이상일 때 실행된다.
int QuickSortInt::selectMedianPivot(int p, int q){
    int start = p;
    int middle = (p + q) / 2;
    int end = q;
    count++;

    // 3개 요소에 대해 정렬
    if(arr[start] > arr[middle]){
        exchange(start, middle);
        if(arr[middle] > arr[end]){
            exchange(middle, end);
            if(arr[start] > arr[middle]){
                exchange(start, middle);
            }
        }
    }
    else if(arr[start] > arr[end]) {
        exchange(start, end);
        if(arr[middle] > arr[end]) {
            exchange(middle, end);
        }
    } else if(arr[middle] > arr[end]) {
        exchange(middle, end);
    }
    return middle;
}

void QuickSortInt::printResult() {
    // cout << "[PRINT START]";
    // for(int i = 0; i < len; i++) {
    //     if( i % 7 == 0) cout << endl;
    //     cout << "[" << arr[i] << "]" << " -> " ;
    // }
    // cout << "[END]" << endl;
    cout << "[PIVOT COUNT] : " << count << endl;
}

void QuickSortInt::exchange(int p, int q) {
    int temp = arr[p];
    arr[p] = arr[q];
    arr[q] = temp;
}

// void QuickSortInt::saveFile() {
//     ifstream file("./daegu_weather_2024_output.txt");
//     file.close();
// }

void QuickSortInt::readFile() {
    ofstream file("./daegu_weather_2024_output.txt");

    file.close();
}

#endif