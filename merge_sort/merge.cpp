#include <iostream>
#include "merge.h"
using namespace std;
 
// [p~m]/[m+1~q] 두 개의 블록에 대해 병합 -> 내림차순으로 정렬
void merge(int list[], int result[], int p, int q, int m) {
    int resultIdx = p;
    int leftStartIdx = p;
    int rightStartIdx = m+1;

    do{
        if(list[leftStartIdx] >= list[rightStartIdx])  result[resultIdx++] = list[leftStartIdx++];
        else                                           result[resultIdx++] = list[rightStartIdx++];
    } while((leftStartIdx <= m && rightStartIdx <= q));

    while(leftStartIdx <= m)      result[resultIdx++] = list[leftStartIdx++];
    while (rightStartIdx <= q)    result[resultIdx++] = list[rightStartIdx++];
    copyResultToList(list, result, p, q);
}

// p와 q는 인덱스
void merge_sort(int list[], int result[], int p, int q) {
    if(p < q) {
        int k = (p+q)/2;
        merge_sort(list, result, p, k);
        merge_sort(list, result, k+1, q);

        // 합병 진행 p ~ q 까지에 대해 비교 하면됨.
        merge(list, result, p, q, k);
    }
}

void printList(int list[], int len){
    cout << ("[INFO] ");
    for(int i = 0; i < len; i++) {
        cout << list[i] << " -> " ;
    }
    cout << ("[END]") << endl;
}

void copyResultToList(int list[], int result[], int p, int q) {
    for(; p <= q; p++){
        list[p] = result[p];
    }
}
