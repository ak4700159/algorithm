#ifndef __SELECTION_H__
#define __SELECTION_H__

#include <iostream>
#include <ctime>

using namespace std;

class Selection{
private:
    // 원본 배열
    int** arr;

    int n;
    int k;
public:
    Selection(int);
    ~Selection();
    // k번째 작은 값 설정
    void setK();
    // MIN 값부터 차례대로 k번째까지 반복해서 찾기
    int execLinear(int, int);
    // 정렬 후 k번째 값 찾기
    int execSort(int , int);
    void exchange(int, int);
    void printN();
};


Selection::Selection(int n) {
    this->n = n;
    srand(time(NULL));
    arr = new int*[n];
   for(int i = 0; i < n; i++) {
        arr[i] = new int[n];
        for(int j = 0; j < n; j++) {
            arr[i][j] = rand() % (100000) + 1;
        }
   }
}

Selection::~Selection() {
    for(int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

// k값 지정
void Selection::setK() {
    k = rand() % (100000) + 1;
}

// 정렬 후 k번째 값 찾기
/*
    1. 피봇 선정
    2. 피봇을 기준으로 정렬
    3. small group size 획득
    4. 3가지 조건식을 통해 
*/
int Selection::execSort(int p, int q) {
    if (p >= q) return;

    int pivotIdx;


    exchange(p, pivotIdx);
    int pivotValue = arr[p / n][p % n];
    // i = left index;
    int i = p + 1;
    // j = right index;
    int j = q;

    while (i <= j) {
        while (i <= q && arr[i / n][i % n] <= pivotValue) i++;
        while (j > p && arr[j / n][j % n] > pivotValue) j--;
        if (i < j) {
            exchange(i, j);
        }
    }

    exchange(p, j); // 피봇 위치 복원


}

// MIN 값부터 차례대로 k번째까지 반복해서 찾기
int Selection::execLinear(int p, int q){


    return 0;
}
 

void Selection::printN() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << "[" << arr[i][j] << "] ->";
        }
        cout << endl;
   }
}

void Selection::exchange(int p, int q) {
    int temp = arr[p/n][p%n];
    arr[p/n][p%n] = arr[q/n][q%n];
    arr[q/n][q%n] = temp;
}

#endif