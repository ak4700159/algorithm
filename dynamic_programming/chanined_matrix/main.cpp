/*
2. 매트릭스 크기에 따른 연산량 증가범위 확인
    2-1. 연속 곱셈이 가능한 랜덤 매트릭스 생성 (5개, 6개,...10개 까지)
    2-2. 각 매트릭스 개수에 따른 최소 연산 횟수 확인
    2-3. 해당 결과를 그래프로 그리고 매트릭스 개수와 연산량 증가와의 연관성 측정 
*/

#include <iostream>
#include "chained_matrix.h"

using namespace std;

int main(void) {
    for(int i = 5; i <= 10; i++) {
        ChainedMatrix chainedMatrix = ChainedMatrix(i);
        chainedMatrix.multiplication();
        // chainedMatrix.printDimensions();
        chainedMatrix.printResult();
        chainedMatrix.printImplicitOrder();
    }
    return 0;
}