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
    int len;                // 메트릭스 길이
    int* d;                 // 메트릭스 길이 정보
    MatrixData** result;    // 매트릭스 연산을 위한 메타데이터

public:
    ChainedMatrix(int l) {
        srand(time(NULL)); // 난수 시드 초기화
        len = l;
        result = new MatrixData*[len];
        for(int i = 0; i < len; i++) {
            result[i] = new MatrixData[len];
        }

        // 대각선 방향 초기화
        for(int i = 0; i < len; i++)
            result[i][i] = MatrixData(0, -1);

        // 매트릭스 길이 정보를 초기화
        // d[0] * d[1] = 첫 번째 메트릭스, d[1] * d[2] = 두 번째 매트릭스, d[2] * d[3] = 세 번째 메트릭스 ...
        // d[l-1] * d[l] = l 번째 메트릭스
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
    // l : 곱셈의 수 | i : 행인덱스(l이 증가함에 따라 최대 인덱스 감소) | j : 열인덱스
    // k : i <= k <= j-1, k값을 바꿔가며 k가 어떤 인덱스일 때 최적의 값을 찾는지 순회
    void multiplication() {
        for(int l = 1; l <= len-1; l++) {
            for(int i = 0; i < len-l; i++) {
                int j = i + l;
                // 목표값 -> i~j까지 메트릭스를 곱했을 때 나오는 최소곱
                result[i][j].setCount(INT_MAX);
                for(int k = i; k < j; k++) {
                    int temp;
                    // result[i][k] -> 행고정 / result[k+1][j] -> 열고정 
                    temp = result[i][k].getCount() + result[k+1][j].getCount() + (d[i] * d[k+1] * d[j+1]);  
                    if(temp < result[i][j].getCount()) {
                        result[i][j].setCount(temp);
                        result[i][j].setK(k);
                    }
                }
            }
        }
    }

    // 연산 순서 출력
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

    // 매트릭스 확장(기존 매트릭스 활용)
    void extendMatrix() {
        // 1. 기존 d 배열의 길이를 늘려 새로운 값 추가
        int* new_d = new int[len + 2]; // 기존 len+1 → len+2
        for (int i = 0; i <= len; i++) {
            new_d[i] = d[i];
        }
        new_d[len + 1] = (rand() % 4 + 1) * 5; // 새로 추가되는 d 값 (5,10,15,20)
        
        delete[] d;
        d = new_d;

        // 2. result 배열을 새 크기로 재할당
        MatrixData** new_result = new MatrixData*[len + 1];
        for (int i = 0; i <= len; i++) {
            new_result[i] = new MatrixData[len + 1];
        }

        // 3. 대각선 초기화
        for (int i = 0; i <= len; i++) {
            new_result[i][i] = MatrixData(0, -1);
        }

        // 기존 result 메모리 해제
        for (int i = 0; i < len; i++) {
            delete[] result[i];
        }
        delete[] result;

        result = new_result;

        // 4. len 증가
        len += 1;

        // 5. 연산 재수행
        // multiplication();
    }
};

#endif