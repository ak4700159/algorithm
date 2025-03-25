#include "quick_sort.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

QuickSort::QuickSort(int len) {
    this->len = len;
    count = 0;
    arr = new int[len] {6, 3, 11, 9,  12, 2, 8, 15, 18, 10, 7, 14};
    result = new int[len] {6, 3, 11, 9,  12, 2, 8, 15, 18, 10, 7, 14};
}

QuickSort::~QuickSort() {
    delete []arr;
    delete []result;
}

// [p, q] => 피벗선정
// 피벗의 왼쪽에 피봇보다 큰값이 오른쪽엔 작은값이 와야된다.
void QuickSort::exec(int p, int q, int type){
    // cout << "[DEBUG] ---------------------------- [START]" << endl;
    // cout << "[INFO] start : " << p << " / end : " << q << endl;
    if((q - p) <= 1) {
        if(arr[p] > arr[q] && (q-p) == 1) {
            exchange(p, q);
            // cout << "[DEBUG] ---------------------------- [END]" << endl << endl;
            return;
        }
        // cout << "[DEBUG] ---------------------------- [END]" << endl << endl;
        return;
    }

    // 피봇 선정
    int newPivotIdx = type == RANDOM ? selectRandomPivot(p, q) : selectMedianPivot(p, q);
    if(p < q) {
        // cout << "[INFO] newPivot index : " << newPivotIdx << " / value : " << arr[newPivotIdx] <<endl;  
        // printResult();
        exchange(p, newPivotIdx);
        newPivotIdx = p;
        count++;
        
        int leftIdx = p + 1;
        int rightIdx = type == RANDOM ? q : q - 1;
        int lastChangeLeftIdx = p + 1; 
        while(true) {
            // cout << "-------------------------------------" << endl;
            // printResult();
            while(arr[newPivotIdx] > arr[leftIdx] && leftIdx < rightIdx) leftIdx++;
            while(arr[newPivotIdx] < arr[rightIdx] && leftIdx < rightIdx) rightIdx--;
            // cout << "[INFO] find left : " << arr[leftIdx] << " / right : " << arr[rightIdx] << endl;
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
                    // cout << "[INFO] wrost case" << endl;
                    int min = lastChangeLeftIdx;
                    for(int i = lastChangeLeftIdx; i <= leftIdx; i++){
                        if(arr[i] < arr[newPivotIdx]) min = i;
                    }
                    if(arr[newPivotIdx] < arr[min]) break;
                    exchange(min, newPivotIdx);
                    newPivotIdx = min;
                }
                else {
                    // cout << "[INFO] best case " << endl;
                    exchange(lastChangeLeftIdx, newPivotIdx);
                    newPivotIdx = lastChangeLeftIdx;
                }
                break;
            }
        }
        // printResult();
        // cout << "[INFO] pivotIdx : " << newPivotIdx << endl;
        // cout << "[DEBUG] ---------------------------- [END]" << endl << endl;
        this->exec(p, newPivotIdx - 1, type);
        this->exec(newPivotIdx + 1, q, type);
    }
}

int QuickSort::selectRandomPivot(int p, int q){
    srand(time(NULL));
    int random =rand() % (q - p + 1) + p; 
    count++;
    cout << "[INFO] " << random << endl;
    return random;
}

// 최소 요소가 3개 이상일 때 실행된다.
int QuickSort::selectMedianPivot(int p, int q){
    int start = p;
    int middle = (p + q) / 2;
    int end = q;

    if(arr[start] > arr[middle]){
        // start <-> middle 교환 
        if(arr[middle] > arr[end]){
            // middle <-> end 교환 
        } 
        else if(arr[start] > arr[end]) {
            // start <-> end 교환
        }
    } else if(arr[start] > arr[end]) {
        // start <-> end 교환
    }
    return middle;
}

void QuickSort::printResult() {
    cout << "[START] ";
    for(int i = 0; i < len; i++) {
        if(i % 5 == 0) cout << endl;
        cout << "[" << result[i] << "] -> ";
    }
    cout << "[END]" << endl << endl;
}

void QuickSort::exchange(int p, int q) {
    result[p] = arr[q];
    result[q] = arr[p];
    arr[p] = result[p];
    arr[q] = result[q];
}


void readFile() {
    ofstream file("./daegu_weather_2024_output.txt");

    file.close();
}

int getLines() {
    int len = 0;
    ofstream file("./daegu_weather_2024_output.txt");


    file.close();
    return len;
}

void QuickSort::saveFile() {
    ifstream file("./daegu_weather_2024_output.txt");

    file.close();

}