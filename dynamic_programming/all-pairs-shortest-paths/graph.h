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
        // 원래 그래프에서 BFS
        bool *visited = new bool[n]{false};
        if (!bfs(arr, 0, visited)) {
            delete[] visited;
            return false;
        }
        delete[] visited;

        // 전치(transpose) 그래프 생성
        int **transpose = new int*[n];
        for (int i = 0; i < n; i++) {
            transpose[i] = new int[n];
            for (int j = 0; j < n; j++) {
                transpose[i][j] = arr[j][i]; // 방향 뒤집기
            }
        }

        // 전치 그래프에서 BFS
        visited = new bool[n]{false};
        bool result = bfs(transpose, 0, visited);

        // 메모리 해제
        for (int i = 0; i < n; i++)
            delete[] transpose[i];
        delete[] transpose;
        delete[] visited;

        return result;
    }

    // 하나의 정점에 대해 모든 정점을 방문하는지 확인
    bool bfs(int **matrix, int start, bool *visited)
    {
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < n; i++)
            {
                if (matrix[cur][i] != 0 && !visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        for (int i = 0; i < n; i++)
            if (!visited[i]) return false;

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
            arr[u][v] = weight; // 방향 그래프: 한 방향만 설정
            edges++;
            // cout << edges << " random edge : (" << u << "," << v << "), weightt: " << weight << endl;
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
