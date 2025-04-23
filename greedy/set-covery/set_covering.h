#ifndef __SET_COVERING_H__
#define __SET_COVERING_H__

#include "setting.h"
#include "subnet.h"
#include <iostream>

using namespace std;

// 과제에선 인덱스가 1부터 시작함 -> 구현상 편의를 위해 0부터 고려
// 출력할 땐 1부터 보이도록함.

class SetCovering
{
private:
    bool u[UNIVERSE_SIZE];     // U 집합 원소 선택 여부(true = 선택 / false = 미선택)
    Subnet *p[POWER_SET_SIZE]; // U 집합의 부분집합 모음
public:
    SetCovering()
    {
        // Subnet(부분 집합의 전체 원소, 집합의 크기, 비용)
        int *s0 = new int[4]{0, 1, 2, 7};       p[0] = new Subnet(s0, 4, 6);
        int *s1 = new int[5]{0, 1, 2, 3, 7};    p[1] = new Subnet(s1, 5, 10);
        int *s2 = new int[4]{0, 1, 2, 3};       p[2] = new Subnet(s2, 4, 4);
        int *s3 = new int[6]{1, 2, 3, 4, 6, 7}; p[3] = new Subnet(s3, 6, 12);
        int *s4 = new int[4]{3, 4, 5, 6};       p[4] = new Subnet(s4, 4, 4);
        int *s5 = new int[5]{4, 5, 6, 8, 9};    p[5] = new Subnet(s5, 5, 8);
        int *s6 = new int[4]{3, 4, 5, 6};       p[6] = new Subnet(s6, 4, 4);
        int *s7 = new int[4]{0, 1, 3, 7};       p[7] = new Subnet(s7, 4, 4);
        int *s8 = new int[2]{5, 8};             p[8] = new Subnet(s8, 2, 3);
        int *s9 = new int[2]{5, 9};             p[9] = new Subnet(s9, 2, 4);

        for (int i = 0; i < UNIVERSE_SIZE; i++)
        {
            u[i] = false;
        }
    }

    // 알고리즘 실행 함수
    void exec()
    {
        // U 집합의 원소가 전부 선택될 때까지
        while (!isEmpty())
        {
            // P 집합의 원소 선택
            int selectedIdx = selectGreedy_v2();
            if(selectedIdx == -1) return;
            p[selectedIdx]->selected = true;
            for (int i = 0; i < p[selectedIdx]->size; i++)
            {
                u[p[selectedIdx]->elements[i]] = true;
            }
            // p[selectedIdx]->print(selectedIdx);
        }
    }

    // 부분 집합 안에 선택되지 않은 원소가 몇 개인지 반환
    int elementCount(int sub)
    {
        int count = 0;
        for (int i = 0; i < p[sub]->size; i++)
        {
            if (!u[p[sub]->elements[i]])
                count++;
        }
        return count;
    }

    // 현재 U 집합이 공집합인지 확인 -> 모든 원소가 선택되어야됨(true 반환)
    bool isEmpty()
    {
        for (int i = 0; i < UNIVERSE_SIZE; i++)
        {
            // 선택되지 않은 원소가 하나라도 있는 경우
            if (!u[i])
                return false;
        }
        return true;
    }

    // 현재 있는 상황에서 탐욕적 선택 -> P 안에서 원소를 선택
    // v1. U와 가장 많이 겹치는 부분 집합 선택
    // v2. 비용이 가장 적게 드는 부분 집합 선택(발생하는 비용 / 겹치는 원소의 수) 
    //          => 겹치는 요소 당 드는 비용이 최소가 되는 것을 선택
    int selectGreedy_v1()
    {
        // 적당히 큰 값으로 초기화 
        int maxIdx = -1;
        int maxCount = -1;
        for (int i = 0; i < POWER_SET_SIZE; i++) 
        {
            if(p[i]->selected) continue;
            int newElements = elementCount(i);

            if(newElements > maxCount)
            {
                maxCount = elementCount(i);
                maxIdx = i;
            }
        }
        return maxIdx;
    }
    int selectGreedy_v2()
    {
        int efficientIdx = -1;
        double efficiency =  1000;
        for (int i = 0; i < POWER_SET_SIZE; i++) 
        {
            if(p[i]->selected || elementCount(i) == 0) continue;
            double newEfficiency = (double)p[i]->cost / elementCount(i);
            if(newEfficiency < efficiency)
            {
                efficiency = newEfficiency;
                efficientIdx = i;
            }
        }
        return efficientIdx;
    }

    // 전체 부분 집합 조회 
    void printSubnets()
    {
        for (int i = 0; i < POWER_SET_SIZE; i++)
        {
            p[i]->print(i);
        }
    }

    // 선택된 부분 집합 조회 
    void printCombind()
    {
        cout << "[INFO] selected subnet list" << endl;
        for (int i = 0; i < POWER_SET_SIZE; i++)
        {
            if (p[i]->selected)
            {
                p[i]->print(i);
            }
        }
    }

    ~SetCovering()
    {
        for (int i = 0; i < POWER_SET_SIZE; i++)
        {
            delete p[i];
        }
    }
};

#endif