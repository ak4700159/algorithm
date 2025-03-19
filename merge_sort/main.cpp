#include "setting.h"
#include "merge.h"
#include <iostream>

using namespace std;

int main() {
    int list[MAX_LIST_SIZE] = {37, 10, 22, 30, 35, 13, 25, 24};
    int result[MAX_LIST_SIZE] = { 0 };
    int listLen = sizeof(list) / 4;
    int resultLen = sizeof(result) / 4;

    // merge_sort(list, result, 0, sizeof(list)/4);
    printList(list, listLen);
    printList(result, resultLen);
    return 0;
}

