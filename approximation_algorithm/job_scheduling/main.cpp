/*
    1. 다음과 같은 작업과 머신이 주어졌을 때, *각 작업을 분배*하여 최종 종료시간을 출력하시오.
        - 작업수 n = 6 (작업시간: 2, 5, 1, 7, 3, 4)
        - 머신 수 m = 3

    출력예시
        머신1: 7
        머신2: 5,1
        머신 3: 4,3,2
        종료시간, 9

    2. 각 작업을 분해할 때, 아래 두가지 방식을 사용하시오.
        a) LPT(Longest Processing Time first)
        b) List Scheduling (순서대로)

    3. 두 방식 모두의 오차율(approximation ratio)을 구하시오.
*/

#include <iostream>
#include "task_scheduler.h"

using namespace std;

int main(void)
{
    int m = 3;
    int n = 6;
    int times[n] = {2, 5, 1, 7, 3, 4};
    Task tasks[n];

    for (int i = 0; i < n; i++)
        tasks[i] = Task(times[i]);

    cout << "[1] LPT " << endl;
    task_scheduler schedulerLPT(n, m, tasks);
    schedulerLPT.scheduleTasks(true);
    schedulerLPT.printResult();

    cout << endl << "[2] List Scheduling " << endl;
    task_scheduler schedulerLinear(n, m, tasks);
    schedulerLinear.scheduleTasks(false);
    schedulerLinear.printResult();

    // 각 알고리즘 방식에 대한 근사해
    double makespanLPT = schedulerLPT.getMakespan();
    double makespanLinear = schedulerLinear.getMakespan();

    // 최적해 구하기 
    double optimalSol = 0.0;
    for(int i = 0; i < n; i++) optimalSol += tasks[i].getTime();
    optimalSol /= m;

    // 근사률 계산
    double LPT_ratio = makespanLPT / optimalSol;
    double Linear_ratio = makespanLinear / optimalSol;

    cout << endl << "[3] LPT approximation rate : " << LPT_ratio << endl;
    cout << "[3] Linear approximation rate : " << Linear_ratio << endl;
    return 0;
}