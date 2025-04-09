#ifndef __PRIM_H__
#define __PRIM_H__

#include "graph.h"

class Prim{
private:
    int n;  // 노드 개수
    int* d; // 노드까지 거리
    int* v; // 노드 방문 여부 
    int* p; // 이전에 방문한 노드가 무엇인지
    Graph graph;

public:
    Prim(int n) : n(n) { 
        d = new int[n] { };
        v = new int[n] { 0 };

        // 
    }
    ~Prim() {
        delete[] d;
        delete[] v;
    }

    void printMST() {

    }

    void searchMST(int start) {

    }

    void updateD() {

    }
};

#endif