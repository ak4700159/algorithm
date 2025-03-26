#include <iostream>
#include "selection.h"

using namespace std;


int main() {
    // 배열 크기 입력 
    int n; cin >> n;
    Selection* selection = new Selection(n);
    selection->setK();

    // MIN 값부터 차례대로 k번째까지 반복해서 찾기
    clock_t startTime = clock();
    // int kValue = selection->execLinear(0, n*n);
    clock_t endTime = clock();
    clock_t elapsedLinear = endTime - startTime;
    cout << "[INFO] execLinear : " << elapsedLinear << " ms" << endl;

    // 정렬 후 k번째 값 찾기
    startTime = clock();
    // kValue = selection->execSort(0, n*n);
    endTime = clock();
    clock_t elapsedSort = endTime - startTime;
    cout << "[INFO] execSort : " << elapsedSort << " ms" << endl;

    if(elapsedLinear > elapsedSort){
        cout << "[INFO] linear search is better than sort search" << endl;
    }
    else if(elapsedLinear < elapsedSort) {
        cout << "[INFO] sort search is better than linear search" << endl;
    }
    else {
        cout << "[INFO] equal." << endl;
    }

    delete selection;
    return 0;
}