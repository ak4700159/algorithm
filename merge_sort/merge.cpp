#include <iostream>
using namespace std;

// 병합할 때 
void merge(int* list, int* result, int p, int q, int k) {
    int* rightList = &list[p];
    int* leftList = &list[k+1];

    while(p < k && k+1 < q){
        
    }
}

// p와 q는 인덱스
void merge_sort(int* list, int* result, int p, int q) {
    if(p < q) {
        int k = (p+q)/2;
        merge_sort(list, result, p, k);
        merge_sort(list, result, k+1, q);

        // 합병 진행 p ~ q 까지에 대해 비교 하면됨.
        merge(list, result, p, q, k);
    }
}

void printList(int* list, int len){
    cout << ("[INFO] ");
    for(int i = 0; i < len; i++) {
        cout << list[i] << " -> " ;
    }
    cout << ("[END]") << endl;
}
