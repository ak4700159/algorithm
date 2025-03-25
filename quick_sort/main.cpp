#include <iostream>
#include "quick_sort.h"

using namespace std;

int main() {
    QuickSort* quickSort = new QuickSort(12);
    quickSort->printResult();
    quickSort->exec(0, 11, MEDIAN);
    quickSort->printResult();
    
    delete quickSort;
    return 0;
}
