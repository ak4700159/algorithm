#ifndef __QUICK_H__
#define __QUICK_H__

#define RANDOM 1
#define MEDIAN 2

#include <fstream>
using namespace std;
class QuickSort{
private:
    // 피봇 선택 카운터
    int count;
    int len;
    int *arr;
    int *result;

public:
    QuickSort(int);
    ~QuickSort();
    void exchange(int, int);
    void exec(int, int, int);
    void printResult();

    int selectRandomPivot(int, int);
    int selectMedianPivot(int, int);
    void select3WayPartitioning(int, int);
    void saveFile();
};

#endif