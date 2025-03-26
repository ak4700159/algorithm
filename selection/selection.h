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
    int execLinear();
    // 정렬 후 k번째 값 찾기
    int execSort();

    void printN();
};


Selection::Selection(int n) {
    this->n = n;
    srand(time(NULL));
    arr = new int*[n];
   for(int i = 0; i < n; i++) {
        arr[i] = new int[n];
        for(int j = 0; j < n; j++) {
            // srand(time(NULL) + j + i);
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
    srand(time(NULL));
    k = rand() % (100000) + 1;
}

// 정렬 후 k번째 값 찾기
/*
    1. 피봇 선정
    2. 피봇을 기준으로 정렬
    3. small group size 획득
    4. 3가지 조건식을 통해 
*/
int Selection::execSort() {




    return 0;
}

// MIN 값부터 차례대로 k번째까지 반복해서 찾기
int Selection::execLinear(){

    
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


#endif