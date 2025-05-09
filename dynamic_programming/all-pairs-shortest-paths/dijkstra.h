#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#define INT_MAX 9999999

#include "graph.h"
#include <iostream>

using namespace std;

class Dijkstra
{
private:
    int n;         // 노드 개수
    int *d;        // 노드까지 거리
    bool *visited; // 노드 방문 여부
    int *p;        // 이전에 방문한 노드가 무엇인지
    Graph* graph;

public:
    Dijkstra(int n, Graph* graph) : n(n), graph(graph)
    {
        d = new int[n];
        visited = new bool[n];
        p = new int[n];

        for (int i = 0; i < n; i++)
        {
            d[i] = INT_MAX;
            visited[i] = false;
            p[i] = -1;
        }
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
                break;
            visited[min] = true;
            // 경로 업데이트
            // cout << "[INFO] shortest node select : " << min << endl;
            for (int v = 0; v < n; v++)
            {
                // 1. 방문하지 않은 정점
                // 2. 간선이 존재
                // 3. 이전 경로 합보다 작아야됨
                int weight = graph->getWeight(min, v);
                if (!visited[v] && d[v] > d[min] + weight && weight != 0)
                {
                    // 경로 변경 (최소로)
                    p[v] = min;
                    d[v] = d[min] + weight;
                    // cout << "[INFO] path update! {" << v << "} : p[]=" << p[v] << "/d[]=" << d[v] << endl;
                }
                else
                {
                    // cout << "[INFO] path update fail {" << v << "}" << endl;
                }
            }
        }
        // printPrevious();
        // printDistance();
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

    void reset() {
        for (int i = 0; i < n; i++)
        {
            d[i] = INT_MAX;
            visited[i] = false;
            p[i] = -1;
        }
    }

    // end index ~~> start index 방향으로 진행
    // 반환값은 총 경로 비용
    int printPath(int v)
    {
        if (p[v] == -1)
        {
            cout << v+1;
            return 0;
        }
        int cost = printPath(p[v]);
        cout << " -> " << v+1;
        return cost + graph->getWeight(v, p[v]);
    }

    void printPrevious()
    {
        cout << "[previous array]" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "p[" << i << "] = ";
            if (p[i] == -1)
                cout << "None";
            else
                cout << p[i];
            cout << ", ";
        }
        cout << endl
             << endl;
    }

    void printDistance()
    {
        cout << "[distance array]" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "d[" << i << "] = ";
            if (d[i] == INT_MAX)
                cout << "INF";
            else
                cout << d[i];
            cout << ", ";
        }
        cout << endl
             << endl;
    }
};

#endif