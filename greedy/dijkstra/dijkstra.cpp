#ifndef __PRIM_H__
#define __PRIM_H__

#include "graph.h"

class Dijkstra
{
private:
    int n;         // 노드 개수
    int *d;        // 노드까지 거리
    bool *visited; // 노드 방문 여부
    int *p;        // 이전에 방문한 노드가 무엇인지
    Graph graph;

public:
    Dijkstra(int n, Graph graph) : n(n), graph(graph)
    {
        d = new int[n]{INT_MAX};
        visited = new bool[n]{false};
        p = new int[n]{-1};
    }
    ~Dijkstra()
    {
        delete[] d;
        delete[] p;
        delete[] visited;
    }

    void searchShortestPath(int start)
    {
        d[start] = 0;

        for (int i = 0; i < n; i++)
        {
            int min = extractMin();
            if (min == -1)
                return;
            d[min] = true;
            // 경로 업데이트
            for (int v; v < n; v++)
            {
                // 1. 방문하지 않은 정점
                // 2. 간선이 존재
                // 3. 이전 경로 합보다 작아야됨
                int weight = graph.getWeight(v, min);
                if (d[v] > d[min] + weight && !visited[v] && weight > 0)
                {
                    // 경로 변경 (최소로)
                    p[v] = min;
                    d[v] = d[min] + weight;
                }
            }
        }
    }

    // 1. 인접한 노드 중
    // 2. 방문하지 않은 노드
    // 3. 그 중에서 최소 경로 선택
    int extractMin()
    {
        int minIdx = -1;
        int minDist = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && d[i] < minDist)
            {
                minIdx = i;
                minDist = d[i];
            }
        }

        return minIdx;
    }

    // v = end
    void printPath(int v)
    {
        if (p[v] == -1)
        {
            cout << v;
            return;
        }
        printPath(p[v]);
        cout << " -> " << v;
    }
};

#endif