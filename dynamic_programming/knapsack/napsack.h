#ifndef __NAPSACK_H__
#define __NAPSACK_H__

#include "item.h"
#include <iostream>
#include <iomanip>

using namespace std;

// 0 1 napsack 알고리즘을 수행
class Napsack {
private:
    int capacity;   // 백팩의 총용량
    Item* items;    // 아이템 리스트
    int itemLength; // 아이템 갯수
    int** result;   // 결과 K테이블
public:
    Napsack(int c, Item* itmes, int l) {
        this->capacity = c;
        this->items = itmes;
        this->itemLength = l;
        result = new int*[itemLength + 1];
        for(int i = 0; i < itemLength + 1; i++) {
            result[i] = new int[capacity + 1] { 0 };
        }
    }

    // 알고리즘 실행 , 기본적인 01-Napsack 알고리즘 실행
    void execAlgorithm() {
        for(int i = 1; i <= itemLength; i++) {
            for(int w = 1; w <= capacity; w++) {
                // 현재 배낭의 무게보다 아이템의 무게가 큰 경우 이전 아이템(i-1)까지 고려한 결과 사용
                if(items[i-1].getWeight() > w) {
                    result[i][w] = result[i-1][w];
                // 배낭에 아이템을 넣을 수 있을 때
                } else {
                    // 현재 아이템(i)을 넣는 것보다 이전 아이템(i-1)까지 고려한 경우 더 높은 가치를 가질 경우
                    if(result[i-1][w] > result[i-1][w-items[i-1].getWeight()] + items[i-1].getCost()) {
                        result[i][w] = result[i-1][w];
                    // 현재 아이템을 넣었을 때 더 가치가 높은 경우
                    } else {
                        result[i][w] = result[i-1][w-items[i-1].getWeight()] + items[i-1].getCost();
                    }
                }
            }
        }
    }

    // 결과 테이블 출력 -> 디버깅용
    void printResult() {
        cout << setw(4) << "I\\W";
        for (int j = 0; j < capacity + 1; j++) {
            cout << setw(3) << j;
        }
        cout << endl;
        for (int i = 0; i < itemLength + 1; i++) {
            cout << setw(4) << i;  // 행 번호
            for (int j = 0; j < capacity + 1; j++) {
                cout << setw(3) << result[i][j];
            }
            cout << endl;
        }
    }

    // 아이템 출력 -> 디버깅용
    void printItems() {
        for(int i = 0; i < itemLength; i++) {
            cout << "Items[" << i << "] " << items[i].getCost() << ", " << items[i].getWeight() << endl; 
        }
    }

    // 선택된 아이템 출력 함수
    void printSelectedItems() {
        int w = capacity;
        for(int i = itemLength; i > 1; i--) {
            // 아이템이 선택되었는지 확인할 수 있는 방법은 i 번째 아이템까지 고려했을 때 무게와 i-1 번째까지 고려했을 때 무게가 같다면
            // 해당 i 번째 아이템은 선택되지 않은 것이다. 이를 이용해 동일하지 않았을 경우 출력하고 무게를 해당 아이템만큼 빼고 
            // 다음 반복문을 진행한다. 
            if(result[i][w] != result[i-1][w]) {
                cout << "selected item{" << i  << "} : " << items[i-1].getCost() << "/"  << items[i-1].getWeight() << endl;
                w -= items->getWeight();
            }
        }
    }

    int getSolution() {
        return result[itemLength+1][capacity+1];
    }
};


#endif