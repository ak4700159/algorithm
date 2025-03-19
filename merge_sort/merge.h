#ifndef __MERGE_H__
#define __MERGE_H__

void printList(int list[], int len);
void merge(int list[], int result[], int p, int q, int k);
void merge_sort(int list[], int result[], int p, int q);
void copyResultToList(int list[], int result[], int p, int q);

#endif