#ifndef __TASK_SCHEDULER_H__
#define __TASK_SCHEDULER_H__

#include "task.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class task_scheduler
{
private:
    Task *task;   // 작업 리스트
    vector<vector<int>> schedule;  // 기계별 작업 기록
    int *l;       // 각 기계의 종료 시간
    int m;        // 기계 수
    int n;        // 작업 수

public:
    task_scheduler(int n, int m, Task *task)
    {
        this->l = new int[m]{0};
        this->m = m;
        this->n = n;
        this->task = new Task[n];
        this->schedule.resize(m);
        for (int i = 0; i < n; i++)
        {
            this->task[i] = task[i];
        }
    }

    ~task_scheduler()
    {
        delete[] task;
        delete[] l;
    }

    void scheduleTasks(bool LPT)
    {
        // 초기화
        for (int i = 0; i < m; i++)
        {
            l[i] = 0;
            schedule[i].clear();
        }

        LPT ? selectLPT() : selectLinear();
    }

    void selectLPT()
    {
        // 주어진 작업을 시간에 대해 내림차순으로 정렬
        sort(task, task + n, [](Task &a, Task &b) {
            return a.getTime() > b.getTime();
        });

        // 정렬된 작업들을 앞에서부터 하나씩 선택해 기계에 배정
        for (int i = 0; i < n; i++)
        {
            int minMachine = findMinMachine();
            l[minMachine] += task[i].getTime();
            task[i].assignmentMachine(minMachine);
            schedule[minMachine].push_back(task[i].getTime());
        }
    }

    void selectLinear()
    {
        // 작업 순서 고려하지 않고 단순 순서대로 작업을 선택해 기계에 배정
        for (int i = 0; i < n; i++)
        {
            int minMachine = findMinMachine();
            l[minMachine] += task[i].getTime();
            task[i].assignmentMachine(minMachine);
            schedule[minMachine].push_back(task[i].getTime());
        }
    }

    int findMinMachine()
    {
        int idx = 0;
        for (int i = 1; i < m; i++)
        {
            if (l[i] < l[idx])
                idx = i;
        }
        return idx;
    }

    int getMakespan()
    {
        int maxTime = l[0];
        for (int i = 1; i < m; i++)
        {
            if (l[i] > maxTime)
                maxTime = l[i];
        }
        return maxTime;
    }

    void printResult()
    {
        for (int i = 0; i < m; i++)
        {
            cout << "machine " << i + 1 << ": ";
            for (int j = 0; j < n; j++)
            {
                if (task[j].getMachine() == i)
                    cout << task[j].getTime() << " ";
            }
            cout << endl;
        }

        cout << "terminated time (makespan): " << getMakespan() << endl;
    }
};

#endif
