/*
2. 매트릭스 크기에 따른 연산량 증가범위 확인
    2-1. 연속 곱셈이 가능한 랜덤 매트릭스 생성 (5개, 6개,...10개 까지)
    2-2. 각 매트릭스 개수에 따른 최소 연산 횟수 확인
    2-3. 해당 결과를 그래프로 그리고 매트릭스 개수와 연산량 증가와의 연관성 측정 
*/

#include <iostream>
#include <fstream>  // 추가
#include "chained_matrix.h"

using namespace std;

int main(void) {
    ofstream outFile("matrix_vs_cost.csv");
    outFile << "matrix_count,min_cost\n";
    ChainedMatrix chainedMatrix = ChainedMatrix(5);
    for(int i = 5; i <= 300; i++) {
        chainedMatrix.multiplication();
        // chainedMatrix.printResult();
        int result = chainedMatrix.getFinalSolution();
        // chainedMatrix.printImplicitOrder();
        // chainedMatrix.printDimensions();
        // 메트릭스 개수와 최적해 간 연관성 확인 
        cout << "(solution / matrix count) = (" << result << " / " << i  << ") : " << (double)result / i << endl;
        outFile << i << "," << (double)result / i << "\n";
        chainedMatrix.extendMatrix();
    }
    outFile.close();
    cout << "📁 CSV saved: matrix_vs_cost.csv\n";
    return 0;
}