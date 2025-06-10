#include <iostream>
#include "napsack.h"
#include "napsack_v2.h"
#include "item.h"
using namespace std;

/*
    1. 기본문제
    아래와 같이 4개의 물건에 대한 무게와 가치가 주었다.
    10kg까지 담을 수 있는 가방이 있을 때, 

    1-1. 가장 가치가 높게 만들 수 있는 물건의 조합(최대 가치)를 구하시오.
    1-2. 어떤 아이템이 선택되었는지 출력하시오.

    Item 1: 5kg, 10만원
    Item 2: 4kg, 40만원
    Item 3: 6kg, 30만원
    Item 4: 3kg, 50만원

    총 배낭 용량: 10kg

    2. 응용문제
    총 가치가 80만원을 넘지 않으면서, 총 무게를 최소로 하는 경우를 구하시오.
    즉, 예산 안에서 가장 가벼운 아이템 조합을 찾으시오.
*/

// 1. 기본 문제에 대한 Solution
void sol1();
// 2. 응용 문제에 대한 Solution
void sol2();

int main() {
    cout << "sol1)" << endl;
    sol1();
    cout << "-----------------------" << endl << endl;
    cout << "sol2)" << endl;
    sol2();
    return 0;
}

void sol1() {
    Item* itmes = new Item[4];
    itmes[0] = Item(10, 5);
    itmes[1] = Item(40, 4);
    itmes[2] = Item(30, 6);
    itmes[3] = Item(50, 3);
    Napsack napsack = Napsack(10, itmes, 4);
    napsack.execAlgorithm();
    napsack.printResult();
    napsack.printSelectedItems();
}

void sol2() {
    Item* itmes = new Item[6];
    itmes[0] = Item(10, 5);
    itmes[1] = Item(40, 4);
    itmes[2] = Item(30, 6);
    itmes[3] = Item(50, 3);
    // itmes[4] = Item(70, 2);
    // itmes[5] = Item(20, 7);
    Napsack2 napsack = Napsack2(80, itmes, 4);
    napsack.execAlgorithm();
    napsack.printResult();
    napsack.printSelectedItems();
}