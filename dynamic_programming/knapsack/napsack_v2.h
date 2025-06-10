#ifndef __NAPSACK_V2_H__
#define __NAPSACK_V2_H__

#include "item.h"
#include <iostream>
#include <iomanip>

#define MAX_INT 9999999

using namespace std;

// 0 1 napsack 알고리즘을 수행
class Napsack2 {
private:
    int value;      // 총 가치
    Item* items;    // 아이템 리스트
    int itemLength; // 아이템 갯수
    int** result;   // 결과 K테이블
public:
    Napsack2(int v, Item* itmes, int l) {
        this->value = v;
        this->items = itmes;
        this->itemLength = l;
        result = new int*[itemLength + 1];
        for(int i = 0; i < itemLength + 1; i++) {
            result[i] = new int[v + 1] { 0 };
        }

        // 첫번째 행은 물건을 고려하지 않았을 때를 의미 -> 값이 매기면 안됨 -> MAX_INT 표현
        for(int i = 0; i <= value; i++) {
            result[0][i] = MAX_INT;
        }

        // 첫번째 열은 보유한 돈이 0원일 때를 의미 -> 선택할 수 있는 아이템이 없음
        for(int i = 0; i <= itemLength; i++) {
            result[i][0] = 0;
        }
    }

    // 알고리즘 실행 
    // 주어진 조건은 두가지 : 사용할 수 있는 총비용, 몇번째 아이템까지 고려하는지
    void execAlgorithm() {
        for(int i = 1; i <= itemLength; i++) {
            for(int v = 1; v <= value; v++) {
                // 현재 아이템의 가치가 담을 수 있는 현재 담을 수 있는 최대 가치보다 큰 경우 이전 값을 그대로 사용
                if(items[i-1].getCost() > v) {
                    result[i][v] = result[i-1][v];
                // 현재 아이템을 담을 수 있는 경우, 최소가 되도록 담으려면 해당 아이템을 넣기전 무게와 해당 아이템을 넣었을 때 무게를 비교해서
                // 더 작은 무게를 가지는 경우를 선택한다. 이런 경우 물건을 넣을 수 있음에도 불구하고 최소 무게를 유지하기 위해서 물건 넣지 않는
                // 경우가 발생한다. 그렇다면? 이를 어떻게 해결할 것인가?
                // 물건을 넣냐 안넣냐로 구분하는 것이 아니라 여러 물건을 넣을 수 있을 때 어떤 물건을 선택할지로 가야할 것 같은데?
                // 위와 같이 구현하게 되면 기존 Napsack 알고리즘과 많이 멀어지게 된다..
                } else {
                    if(result[i-1][v] > result[i-1][v - items[i-1].getCost()] + items[i-1].getWeight()) {
                        result[i][v] = result[i-1][v - items[i-1].getCost()] + items[i-1].getWeight();
                    } else {
                        result[i][v] = result[i-1][v];
                    }
                }
            }
        }
    }

    // 결과 테이블 출력 -> 디버깅용
    void printResult() {
        cout << setw(4) << "I\\V";
        for (int j = 0; j < value + 1; j++) {
            cout << setw(3) << j;
        }
        cout << endl;
        for (int i = 0; i < itemLength + 1; i++) {
            cout << setw(4) << i;  // 행 번호
            for (int j = 0; j < value + 1; j++) {
                if(result[i][j] == MAX_INT) {
                    cout << setw(3) << "F";
                } else {
                    cout << setw(3) << result[i][j];
                }            
            }
            cout << endl;
        }
    }

    // 선택된 아이템 출력 함수
    void printSelectedItems() {
        int v = value;
        for(int i = itemLength; i > 1; i--) {
            // 아이템이 선택되었는지 확인할 수 있는 방법은 i 번째 아이템까지 고려했을 때 무게와 i-1 번째까지 고려했을 때 무게가 같다면
            // 해당 i 번째 아이템은 선택되지 않은 것이다. 이를 이용해 동일하지 않았을 경우 출력하고 무게를 해당 아이템만큼 빼고 
            // 다음 반복문을 진행한다. 
            if(result[i][v] != result[i-1][v]) {
                cout << "selected item{" << i  << "} : " << items[i-1].getWeight() << "/"  << items[i-1].getCost() << endl;
                v -= items->getCost();
            }
        }
    }

    // 최종해 반환
    int getSolution() {
        return result[itemLength][value];
    }
};


#endif