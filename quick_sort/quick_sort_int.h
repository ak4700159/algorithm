#ifndef __QUICK_INT_H__
#define __QUICK_INT_H__

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include "setting.h"
using namespace std;

class QuickSort{
private:
    // 피봇 선택 카운터
    int count;
    int len;
    int *arr;
    int *result;

public:
    QuickSort(int);
    ~QuickSort();
    void exchange(int, int);
    void exec2WayPartitioning(int, int, int);
    void exec3WayPartitioning(int, int);

    int selectRandomPivot(int, int);
    int selectMedianPivot(int, int);
    void printResult();
    void readFile();
    void saveFile();
};

// {6, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2, 2}
// {6, 3, 11, 9,  12, 2, 8, 15, 18, 10, 7, 14}
QuickSort::QuickSort(int len) {
    this->len = len;
    count = 0;
    arr = new int[len];
    result = new int[len];
}

QuickSort::~QuickSort() {
    delete []arr;
    delete []result;
}

// [p, q] => 피벗선정
// 피벗의 왼쪽에 피봇보다 큰값이 오른쪽엔 작은값이 와야된다.
void QuickSort::exec2WayPartitioning(int p, int q, int type){
    if((q - p) <= 1) {
        if(arr[p] > arr[q] && (q-p) == 1) {
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
            while(arr[newPivotIdx] > arr[leftIdx] && leftIdx < rightIdx) leftIdx++;
            while(arr[newPivotIdx] < arr[rightIdx] && leftIdx < rightIdx) rightIdx--;
            if((leftIdx < rightIdx) && (arr[newPivotIdx] < arr[leftIdx]) && (arr[newPivotIdx] > arr[rightIdx])) {
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
                        if(arr[i] < arr[newPivotIdx]) min = i;
                    }
                    if(arr[newPivotIdx] < arr[min]) break;
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

void QuickSort::exec3WayPartitioning(int p, int q){
    if((q - p) <= 1) {
        if(arr[p] > arr[q] && (q-p) == 1) {
            exchange(p, q);
            return;
        }
        return;
    }

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

int QuickSort::selectRandomPivot(int p, int q){
    srand(time(NULL));
    int random =rand() % (q - p + 1) + p; 
    count++;
    return random;
}

// 최소 요소가 3개 이상일 때 실행된다.
int QuickSort::selectMedianPivot(int p, int q){
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

void QuickSort::printResult() {
    cout << "[START] ";
    for(int i = 0; i < len; i++) {
        if(i % 5 == 0) cout << endl;
        cout << "[" << result[i] << "] -> ";
    }
    cout << "[END]" << endl;
    cout << "[PIVOT COUNT] : " << count << endl << endl;
}

void QuickSort::exchange(int p, int q) {
    result[p] = arr[q];
    result[q] = arr[p];
    arr[p] = result[p];
    arr[q] = result[q];
}

void QuickSort::saveFile() {
    ifstream file("./daegu_weather_2024_output.txt");

    file.close();
}

void QuickSort::readFile() {
    ofstream file("./daegu_weather_2024_output.txt");

    file.close();
}

#endif