#ifndef __CHAINED_MATRIX_H__
#define __CHAINED_MATRIX_H__

#include <iostream>
#include <climits>
#include <iomanip>
#include <ctime>  
#include <cstdlib>
#include "matrix_data.h"

using namespace std;

class ChainedMatrix {
private:
    int len;
    int* d;
    MatrixData** result;

public:
    ChainedMatrix(int l) {
        srand(time(NULL)); // 난수 시드 초기화
        len = l;
        result = new MatrixData*[len];
        for(int i = 0; i < len; i++) {
            result[i] = new MatrixData[len];
        }

        for(int i = 0; i < len; i++)
            result[i][i] = MatrixData(0, -1);

        d = new int[l + 1];
        for(int i = 0; i < l + 1; i++) {
            d[i] = (rand() % 4 + 1) * 5;
        }
    }

    ~ChainedMatrix() {
        delete[] d;
        for (int i = 0; i < len; i++)
            delete[] result[i];
        delete[] result;
    }

    void printResult() {
        cout << "Chained Matrix Multipulication" << endl;
        cout << "==================================" << endl;

        cout << setw(4) << "M";
        for (int j = 0; j < len; j++) {
            cout << setw(6) << (j + 1);
        }
        cout << endl;
        for (int i = 0; i < len; i++) {
            cout << setw(4) << (i + 1);  // 행 번호
            for (int j = 0; j < len; j++) {
                if (i <= j)
                    cout << setw(6) << result[i][j].getCount();
                else
                    cout << setw(6) << " ";
            }
            cout << endl;
        }

        // 최종해 출력
        cout << "Final Solution : " << getFinalSolution() << endl;
    }

    // 여기서 조심할 것은 인덱스 파트다. 인덱스는 0부터 시작이기에 이를 유념해서 알고리즘을 구현해야 한다.
    // j, i, k는 인덱스로 활용
    void multiplication() {
        for(int l = 1; l <= len - 1; l++) {
            for(int i = 0; i < len - l; i++) {
                int j = i + l;
                result[i][j].setCount(INT_MAX);
                for(int k = i; k < j; k++) {
                    int temp;
                    // result[i][k] -> 행고정 
                    // result[k+1][j]
                    temp = result[i][k].getCount() + result[k+1][j].getCount() + (d[i] * d[k+1] * d[j+1]);  
                    if(temp < result[i][j].getCount()) {
                        result[i][j].setCount(temp);
                        result[i][j].setK(k);
                    }
                }
            }
        }
    }

    void printImplicitOrder() {
        cout << "Implicit Order for Matrix Multiplication : ";
        print(0, len - 1);
        cout << "\n";
    }

    // 재귀함수 호출
    void print(int start, int end) {
        // 끝에 도달한 경우
        if (start == end) {
            cout << "A" << start + 1;
            return;
        }

        // 예외 처리
        int k = result[start][end].getK();
        if (k < 0 || k >= len) {
            cout << "[Invalid K]";
            return;
        }

        // K값을 기준으로 함수 호출
        cout << "(";
        print(start, k);
        cout << " * ";
        print(k + 1, end);
        cout << ")";
    }

    // 최종해 출력
    int getFinalSolution() {
        return result[0][len-1].getCount();
    }

    void printDimensions() {
        cout << "Matrix Dimensions (d): ";
        for (int i = 0; i <= len; i++) {
            cout << d[i] << " ";
        }
        cout << endl;
    }
};

#endif