#ifndef __SELECTION_H__
#define __SELECTION_H__

#include <iostream>
#include <ctime>

using namespace std;

class Selection{
private:
    // 원본 배열
    int** arr;
    int** copyArr;
    int n;
public:
    Selection(int);
    ~Selection();
    // MIN 값부터 차례대로 k번째까지 반복해서 찾기
    int execLinear(int, int, int);
    // 정렬 후 k번째 값 찾기
    int execSort(int , int, int);
    void exchange(int, int);
    void printN();
    void copy();
};

Selection::Selection(int n) {
    this->n = n;
    srand(time(NULL));
    arr = new int*[n];
    copyArr = new int*[n];
   for(int i = 0; i < n; i++) {
        arr[i] = new int[n];
        copyArr[i] = new int[n];
        for(int j = 0; j < n; j++) {
            arr[i][j] = rand() % (100000) + 1;
            copyArr[i][j] = arr[i][j];
        }
   }
}

Selection::~Selection() {
    for(int i = 0; i < n; i++) {
        delete[] arr[i];
        delete[] copyArr[i];
    }
    delete[] arr;
    delete[] copyArr;
}

// k값 지정
int initSetK() {
    int k = rand() % (100000) + 1;
    return k;
}

// 정렬 후 k번째 작은 값 찾기
/*
    1. 피봇 선정
    2. 피봇을 기준으로 정렬
    3. small group size 획득
    4. 3가지 조건식을 통해 
*/
int Selection::execSort(int p, int q, int k) {
    if (q - p + 1 < k) return -1;
    if (p == q) return arr[p/n][p%n];

    int pivotValue = arr[p/n][p%n];
    // cout << "[INFO] pivotValue : " << pivotValue << endl;
    int leftDuplicatedIdx = p;
    int rightDuplicatedIdx = q;
    int i = p;
    while(i <= rightDuplicatedIdx) {
        if (arr[i/n][i%n] < pivotValue) {
            exchange(i, leftDuplicatedIdx);
            leftDuplicatedIdx++;
            i++;
        } else if (arr[i/n][i%n] > pivotValue) {
            exchange(i, rightDuplicatedIdx);
            rightDuplicatedIdx--;
        } else {
            i++;
        }
    }
    
    // 왼쪽 그룹(피봇보다 작은 원소들)의 크기
    int numLess = leftDuplicatedIdx - p;
    // 피봇과 같은 원소들의 개수 (중간 그룹)
    int numEqual = rightDuplicatedIdx - leftDuplicatedIdx + 1;
    
    if (k <= numLess) {
        // cout << "[INFO] " << rightDuplicatedIdx + 1 << " ~ " << q << " |  k : " << k - numLess - numEqual << endl;
        return execSort(p, leftDuplicatedIdx - 1, k);
    } else if (k > numLess + numEqual) {
        // cout << "[INFO] " << rightDuplicatedIdx + 1 << " ~ " << q << " |  k : " << k - numLess - numEqual << endl;
        return execSort(rightDuplicatedIdx + 1, q, k - numLess - numEqual);
    } else {
        // cout << "[INFO] pivot search!" << endl;
        return pivotValue;
    } 
}

// MIN 값부터 차례대로 k번째까지 반복해서 찾기(K번째 작은 값 찾기)
int Selection::execLinear(int p, int q, int k){
    const int MAX_VALUE = 1000000;
    int minValue; int minIdx;
    int kCount = 0;
    while (kCount < k) {
        minValue = MAX_VALUE; 
        minIdx = -1;         
        // 전체 중 가장 작은 값 검색
        for(int j = p; j <= q; j++) {
            if(arr[j/n][j%n] < minValue){
                minValue = arr[j/n][j%n];
                minIdx = j;
            }
        }
        if(minIdx == -1) break;
        arr[minIdx/n][minIdx%n] = MAX_VALUE;
        kCount++;
        // if(kCount % 5 == 0) cout << "[INFO] kCount : " << kCount << endl; 
    }
    return minValue;
}
 
void Selection::printN() {
//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < n; j++) {
//             cout << "[" << arr[i][j] << "] ->";
//         }
//         cout << endl;
//    }
//    cout << "---------------------" << endl;
    for(int i = 0; i < n*n; i++){
        cout << "[" << arr[i/n][i%n] << "] ->";
        if((i+1)%n == 0) cout << endl;
    }
}

void Selection::exchange(int p, int q) {
    int temp = arr[p/n][p%n];
    arr[p/n][p%n] = arr[q/n][q%n];
    arr[q/n][q%n] = temp;
    // cout << "[INFO] " << arr[p/n][p%n] <<  " <-> " << arr[q/n][q%n] << endl;
}

void Selection::copy() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            arr[i][j] = copyArr[i][j];
    }
}

#endif