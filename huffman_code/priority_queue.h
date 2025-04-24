#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

/*
Heap은 테이터를 특정한 기준으로 정렬하는 알고리즘이다 -> 배열을 이용해 구현한다.
- 0번째 인덱스는 비워둔다
- (부모 인덴스 * 2) = 왼쪽 자식 인덱스
- (부모 인덴스 * 2) + 1 = 오른쪽 자식 인덱스
- 자식 인덱스 / 2 = 부모 인덱스
*/

#include "node.h"
#include <iostream>
using namespace std;

// 최소
class Heap
{
private:
    int size;
    Node **arr;

public:
    Heap() {}
    Heap(int n)
    {
        size = 0;
        arr = new Node*[n + 1];
        for (int i = 0; i < n; i++)
        {
            arr[i] = new Node();
        }
    }

    void insert(Node* newNode)
    {
        arr[++size] = newNode;
        for (int i = size; i > 1; i /= 2)
        {
            if (arr[i]->frequcncy < arr[i / 2]->frequcncy)
            {
                swap(i, i / 2);
            }
            else
            {
                break;
            }
        }
    }

    Node* remove()
    {
        // 비어있으면 return
        if (size < 1)
            return nullptr;
        Node* remove = arr[1];
        // 맨마지막에 있는 노드를 루트 노드로 선정한다.
        arr[1] = arr[size--];
        for (int i = 1; i * 2 <= size;)
        {
            int left = i * 2;
            int right = i * 2 + 1;
            int small = left;
            if (right <= size && arr[right]->frequcncy < arr[left]->frequcncy)
            {
                small = right;
            }

            if (arr[small]->frequcncy > arr[i]->frequcncy)
            {
                break;
            }

            swap(i, small);
            i = small;
        }
        return remove;
    }

    void swap(int a1, int a2)
    {
        Node* temp = arr[a1];
        arr[a1] = arr[a2];
        arr[a2] = temp;
    }

    void printHeap()
    {
        std::cout << "[INFO] Heap Contents\n";
        for (int i = 1; i <= size; ++i)
        {
            std::cout << "[IDX] " << i << ": ";
            arr[i]->printNode();
        }
    }

    // 일단 작성 나중에 쓸 일이 있을 것으로 보임.
    int getSize() const
    {
        return size;
    }

    // Heap이 제대로 만들어졌는지 검증하는 함수
    bool validateMinHeap(int idx = 1)
    {
        if (idx > size)
            return true;

        int left = idx * 2;
        int right = idx * 2 + 1;

        if (left <= size && arr[idx]->frequcncy > arr[left]->frequcncy)
            return false;
        if (right <= size && arr[idx]->frequcncy > arr[right]->frequcncy)
            return false;

        return validateMinHeap(left) && validateMinHeap(right);
    }
};

#endif