#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <queue>
#include "edge.h"

using namespace std;

class Graph
{
private:
    int n;
    int edges;
    int **arr;

    // 연결형 그래프인지 확인
    bool isConnected()
    {
        bool *visited = new bool[n]{false};
        queue<int> q;

        // 0번째 인덱스를 가지는 정점부터 검사 시작 -> 전부 연결되어 있으면 성공
        q.push(0);
        visited[0] = true;

        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < n; i++)
            {
                // 값이 0이면 연결되어 있지 않음을 의미
                // 간선이 놓여져 있으면서 방문하지 않은 정점
                if (arr[cur][i] != 0 && !visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                delete[] visited;
                return false;
            }
        }

        delete[] visited;
        return true;
    }

public:
    Graph() {}
    Graph(int n)
    {
        this->n = n;
        this->edges = 0;
        arr = new int *[n];
        for (int i = 0; i < n; i++)
        {
            arr[i] = new int[n];
            for (int j = 0; j < n; j++)
            {
                arr[i][j] = 0;
            }
        }
        srand(time(0));
    }
    ~Graph()
    {
        for (int i = 0; i < n; i++)
        {
            delete[] arr[i];
        }
        delete[] arr;
    }

    int getEdges()
    {
        return edges;
    }
    int getVertices()
    {
        return n;
    }

    void setConnectedGraph()
    {
        bool isFirst = true;
        while (!isConnected())
        {
            int u = rand() % n;
            int v = rand() % n;
            if (u == v || arr[u][v] != 0)
                continue;

            int weight = rand() % 100 + 1;
            arr[u][v] = arr[v][u] = weight;
            if (isFirst)
            {
                isFirst = false;
            }
            edges++;
            cout << edges << " random edge : (" << u << "," << v << "), (" << v << "," << u << "), weightt: " << weight << endl;
        }
        cout << "Number of Vertices : " << n << endl;
        cout << "Number of Edges : " << edges << endl;
        // printGraph();
    }

    void printGraph()
    {
        cout << "    ";
        for (int j = 0; j < n; j++)
        {
            cout << setw(3) << j << " ";
        }
        cout << endl;

        cout << "    ";
        for (int j = 0; j < n; j++)
        {
            cout << "----";
        }
        cout << endl;

        for (int i = 0; i < n; i++)
        {
            cout << setw(2) << i << " |";
            for (int j = 0; j < n; j++)
            {
                cout << setw(3) << arr[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void addEdge(int v, int u, int w)
    {
        arr[u][v] = w;
        arr[v][u] = w;
        edges++;
    }

    int getWeight(int v, int u)
    {
        return arr[u][v];
    }
};

#endif
