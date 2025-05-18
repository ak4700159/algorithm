#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <cstdlib>

using namespace std;

class Matrix {
private:
    int** arr;   // 값
    int row;     // 행의 크기
    int column;  // 열의 크기

public:
    // 이전 메트릭스의 높이값
    // -> 높이 고정, 세로 랜덤( 5 ~ 20 )  
    // 값은 0 ~ 100 까지 값으로 구성
    Matrix(int preRow) {
        // 이전 매트릭스가 없으면 0
        if(preRow == 0) {    
            column = rand() % 20 + 1;
        } else {
            column = preRow;
        }
        row = rand() % 20 + 1;

        arr = new int*[column];
        for(int i = 0; i < column; i++) {
            arr[i] = new int[row];
        }

        for(int i = 0; i < column; i++) {
            for(int j = 0; j < row; i++) {
                arr[i][j] = rand() % 100 + 1;
            }
        }
    }

    // 빈 매트릭스 
    Matrix() {
        row = column = 0;
        arr = nullptr;
    }

    ~Matrix() {
        if(arr != nullptr) {
            for(int i = 0; i < column; i++) {
                delete[] arr[i];
            }
            delete[] arr;
        }
    }

    int getRow() {
        return row;
    }

    int getColumn() {
        return column;
    }

    // this = 좌측 매트릭스 * m = 우측 매트릭스
    Matrix operator*(const Matrix& m) {
        if(this->row != m.column) {
            cout << "[ERROR] matrix multipulication error..." << endl;
            exit(1);
        }
        Matrix tmp;
        tmp.row = column;
        tmp.column = m.row;

        tmp.arr = new int*[tmp.column];
        for(int i = 0; i < tmp.column; i++) {
            tmp.arr[i] = new int[tmp.row];
        }

        for(int i = 0; i < tmp.column; i++) {
            for(int j = 0; j < tmp.row; j++) {
                int sum = 0;
                for(int k = 0; k < row; k++) {
                    sum += m.arr[j][k] * this->arr[k][j];
                }
                tmp.arr[i][j] = sum;
            }
        }
        return tmp;
    }
};

#endif