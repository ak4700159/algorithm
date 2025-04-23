#ifndef __SUBNET_H__
#define __SUBNET_H__

#include <iostream> 
using namespace std;

// 부분집합 클래스
class Subnet
{
public:
    Subnet() : elements(nullptr), size(0), cost(0), selected(false) {}
    Subnet(int *elements, int size, int cost) : size(size), cost(cost)
    {
        this->elements = elements;
        this->selected = false;
    }
    ~Subnet()
    {
        delete elements;
    }

    void print(int idx) {
        {
            cout << "S" << idx + 1 << " (cost: " << cost << " ) : { ";
            for (int j = 0; j <size; j++)
            {
                cout << elements[j] + 1; // 0-based → 1-based 출력
                if (j < size - 1)
                    cout << ", ";
            }
            cout << " }" << endl;
        }
    }

    bool selected; // 집합 선택 여부
    int *elements; // 집합 안의 요소(value = index)
    int size;      // 총 사이즈
    int cost;      // 비용
};

#endif 