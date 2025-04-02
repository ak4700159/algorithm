#ifndef __KRUSKAL_H__
#define __KRUSKAL_H__

#include "graph.h"
#include "edge.h"
#include <iostream>
using namespace std;

class Kruskal
{
private:
    Graph graph;
    Graph mst;
    Edge *edges;

public:
    Kruskal(Graph graph) : mst(graph.getVertices()), graph(graph)
    {
        this->edges = new Edge[graph.getEdges()];
        int count = 0;
        // 간선 초기화
        for (int i = 0; i < graph.getVertices(); i++)
        {
            for (int j = i + 1; j < graph.getVertices(); j++)
            {
                if (graph.getWeight(i, j) != 0)
                    edges[count++] = Edge(i, j, graph.getWeight(i, j));
            }
        }

        // 간선 오름차순으로 정렬
        ascendingSort();
        // printEdges();
    }
    ~Kruskal()
    {
        delete[] edges;
    }

    // kruskal 알고리즘 구현
    // first == true 첫번째로 생성한 간선을 반드시 포함.
    void searchMST(bool first)
    {
        int n = graph.getVertices();
        int edgeCount = graph.getEdges();
        int *parent = new int[n];
        for (int i = 0; i < n; i++)
            parent[i] = i;

        // 선택된 간선의 수
        int selectedCount = 0;
        // 현재 비교될 간선
        int i = 0;
        // 첫번째로 생성한 간선
        Edge firstE = graph.getFirstEdge();
        while (selectedCount < (n - 1) && i < edgeCount)
        {
            Edge e;
            if(selectedCount == 0 && first) {
                e = firstE;
            } else {
                if(edges[i].end == firstE.end && edges[i].start == firstE.start && first){
                    i++; continue;
                }
                e = edges[i++];
            }
            int a = find(e.start, parent);
            int b = find(e.end, parent);
            // 같은 집합은 루트 정점이 동일하다.
            // 같은 집합일 경우 병합하면 사이클이 생기게 된다.
            if (a != b)
            {
                unite(a, b, parent);
                mst.addEdge(e.start, e.end, e.weight);
                selectedCount++;
            }
            else
            {
                printf("edge (%d,%d) is excluded because it creates a cycle\n", e.start, e.end);
            }
        }
        delete[] parent;
    }

    void ascendingSort()
    {
        for (int i = 0; i < graph.getEdges(); i++)
        {
            int min = i;
            for (int j = i + 1; j < graph.getEdges(); j++)
            {
                if (edges[min].weight > edges[j].weight)
                {
                    min = j;
                }
            }
            swap(edges[i], edges[min]);
        }
    }

    void printMST()
    {
        mst.printGraph();
    }

    void printEdges()
    {
        for (int i = 0; i < graph.getEdges(); i++)
        {
            printf("%2d. %d <-> %d | %d\n", i + 1, edges[i].start, edges[i].end, edges[i].weight);
        }
    }

    // x 정점의 루트 정점을 찾는다.
    int find(int x, int *parent)
    {
        if (parent[x] != x) parent[x] = find(parent[x], parent);
        return parent[x];
    }

    // 정점 a가 속한 집합과 정점 b과 속한 집합을 병합한다.
    // b의 집합은 a의 집합에 들어가게 된다.
    void unite(int a, int b, int *parent)
    {
        a = find(a, parent);
        b = find(b, parent);
        if (a != b) parent[b] = a;
    }
};

#endif
