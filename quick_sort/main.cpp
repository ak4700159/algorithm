#include <iostream>
#include "quick_sort_int.h"

using namespace std;

int main() {
    QuickSort* quickSort = new QuickSort(12);
    quickSort->printResult();
    quickSort->exec3WayPartitioning(0, 11);
    quickSort->printResult();
    
    delete quickSort;
    return 0;
}
