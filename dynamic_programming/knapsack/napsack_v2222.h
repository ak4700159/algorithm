// #ifndef __NAPSACK_V2_H__
// #define __NAPSACK_V2_H__

// #include "item.h"
// #include <iostream>
// #include <iomanip>
// #define MAX_INT 9999999

// using namespace std;


// // 주여진 가치 안에서 최소가 되는 아이템 조합을 찾아야된다.
// // 즉, result[itemLength+1][cost+1]에는 모든 아이템을 고려했을 때
// // 최소가 되는 무게가 저장된다.
// class Napsack2 {
// private:
//     int cost;       // 주어진 최대 가치
//     Item* items;    // 아이템 리스트
//     int itemLength; // 아이템 갯수
//     int** result;   // 결과 K테이블
// public:
//     Napsack2(int c, Item* itmes, int l) {
//         this->cost = c;
//         this->items = itmes;
//         this->itemLength = l;
//         result = new int*[itemLength + 1];
//         for (int i = 0; i <= itemLength; ++i) {
//             result[i] = new int[cost + 1];
//             for (int j = 0; j <= cost; ++j) {
//                 result[i][j] = MAX_INT;
//             }
//         }
//         result[0][0] = 0;  // 시작 상태만 0
//     }

//     // 알고리즘 실행 , 기본적인 01-Napsack 알고리즘 실행
//     // 기존 알고리즘과 달리 고려해야될 위에서 0으로 초기화 했기에 아직 물건을 아무것도 넣지 않았고 i 번째 물건을 넣을 수 있다면
//     // 해당 물건을 넣어야 된다. 이렇게 물건을 넣을 수 있때마다 넣으면 넣은 물건들의 합이 최소가 되어야한다
//     void execAlgorithm() {
//         for (int i = 1; i <= itemLength; i++) {
//             for (int c = 0; c <= cost; c++) {
//                 int itemCost = items[i-1].getCost();
//                 int itemWeight = items[i-1].getWeight();

//                 // 이전까지의 결과 그대로 유지
//                 result[i][c] = result[i-1][c];

//                 // 넣을 수 있으면 반드시 넣는다
//                 if (c >= itemCost && result[i-1][c - itemCost] != MAX_INT) {
//                     int withItem = result[i-1][c - itemCost] + itemWeight;
//                     result[i][c] = min(result[i][c], withItem); // 최소 무게 선택
//                 }
//             }
//         }
//     }

//     // 결과 테이블 출력 -> 디버깅용
//     void printResult() {
//         cout << setw(4) << "I\\W";
//         for (int j = 0; j < cost + 1; j++) {
//             cout << setw(4) << j;
//         }
//         cout << endl;
//         for (int i = 0; i < itemLength + 1; i++) {
//             cout << setw(4) << i;  // 행 번호
//             for (int j = 0; j < cost + 1; j++) {
//                 if(result[i][j] == MAX_INT) {
//                     cout << setw(4) << "INF";
//                 } else {
//                     cout << setw(4) << result[i][j];
//                 }
//             }
//             cout << endl;
//         }
//     }

//     int getBestCost() {
//         int minWeight = MAX_INT;
//         int best = 0;
//         for (int c = 0; c <= cost; ++c) {
//             if (result[itemLength][c] < minWeight) {
//                 minWeight = result[itemLength][c];
//                 best = c;
//             }
//         }
//         return best;
//     }

//     void printSelectedItems() {
//         int c = getBestCost();  // 가장 좋은 조합의 cost
//         for (int i = itemLength; i > 0; i--) {
//             int itemCost = items[i - 1].getCost();
//             int itemWeight = items[i - 1].getWeight();

//             // 아이템이 선택된 경우는 result 값이 위와 다를 때!
//             if (c >= itemCost &&
//                 result[i][c] == result[i - 1][c - itemCost] + itemWeight) {
//                 cout << "selected item{" << i << "} : "
//                     << itemCost << "/" << itemWeight << endl;
//                 c -= itemCost;  // 선택된 아이템의 비용만큼 차감
//             }
//         }
//     }

//     int getSolution() {
//         return result[itemLength][cost];
//     }
// };


// #endif