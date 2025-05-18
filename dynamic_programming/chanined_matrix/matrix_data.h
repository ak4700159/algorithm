#ifndef __MATRIX_DATA_H__
#define __MATRIX_DATA_H__

#include "matrix.h"

class MatrixData {
private:
    int count;       // 최적의 곱셈수
    int k;           //  C[i, k]  * C[k + 1, j] 
public:
    MatrixData(int count, int k) : count(count), k(k) { }
    MatrixData() : count(0), k(0) { }

    int getCount() {
        return count;
    }

    int getK() {
        return k;
    }

    void setCount(int count) {
        this->count = count;
    }

    void setK(int k) {
        this->k = k;
    }
};


#endif