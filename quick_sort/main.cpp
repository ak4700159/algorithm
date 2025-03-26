#include <iostream>
#include "quick_sort_int.h"
#include "quick_sort_weather.h"

using namespace std;

void sol1();
void sol2();
void sol3();

int main() {
    sol1();
    sol2();
    sol3();
    return 0;
}

void sol1() {
    cout << "[SOL1] 2-way partitioning : MID pivot select in static list" << endl;
    QuickSortInt* quickSort = new QuickSortInt(12);
    quickSort->exec2WayPartitioning(0, 11, MID);
    quickSort->printResult();
    cout << endl << endl;
    delete quickSort;
}


void sol2() {
    cout << "[SOL2] 2-way partitioning : RANDOM pivot select and MEDIAN pivot select in data" << endl;
    int len = getLines();
    QuickSortWeather* quickSort = new QuickSortWeather(len);
    quickSort->readFile();
    quickSort->exec2WayPartitioning(0, len-1, RANDOM);
    // quickSort->printResult();
    int random = quickSort->getCount();
    quickSort->initCount();

    quickSort->readFile();
    quickSort->exec2WayPartitioning(0, len-1, MEDIAN);
    // quickSort->printResult();
    int median = quickSort->getCount();

    cout << "median : " << median << " / " << "random : " << random << endl; 
    if(random > median) {
        cout << "median selection is better than random selection" ;
    }
    else if(random < median) {
        cout << "selection selection is better than random median" ;
    }
    else {
        cout << "equal.";
    }
    cout << endl << endl;
    delete quickSort;
}

void sol3() {
    cout << "[SOL3] 3-way partitioning in data" << endl;
    int len = getLines();
    QuickSortWeather* quickSort = new QuickSortWeather(len);
    quickSort->readFile();
    quickSort->exec3WayPartitioning(0, len-1);
    quickSort->printResult();
    cout << endl << endl;
    delete quickSort;
}