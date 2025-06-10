#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <queue>

using namespace std;

class Graph
{
private:
    int n;
    int edges;
    int **arr;

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
    Graph()
    {
        // 정점의 갯수 10  ~ 20개까지
        n = rand() % 11 + 10;
        edges = 0;
        arr = new int *[n];
        for (int i = 0; i < n; i++)
        {
            arr[i] = new int[n]{0};
        }
    }
    Graph(const Graph &other)
    {
        n = other.n;
        edges = other.edges;

        arr = new int *[n];
        for (int i = 0; i < n; ++i)
        {
            arr[i] = new int[n];
            for (int j = 0; j < n; ++j)
            {
                arr[i][j] = other.arr[i][j];
            }
        }
    }

    Graph &operator=(const Graph &other)
    {
        if (this == &other)
            return *this; // 자기 자신과의 대입 방지

        // 기존 자원 해제
        for (int i = 0; i < n; ++i)
            delete[] arr[i];
        delete[] arr;

        // 새 값 복사
        n = other.n;
        edges = other.edges;
        arr = new int *[n];
        for (int i = 0; i < n; ++i)
        {
            arr[i] = new int[n];
            for (int j = 0; j < n; ++j)
            {
                arr[i][j] = other.arr[i][j];
            }
        }
        return *this;
    }

    ~Graph()
    {
        for (int i = 0; i < n; i++)
            delete[] arr[i];
        delete[] arr;
    }

    // unweighted + undirected 그래프 생성
    void setRandomGraph()
    {
        // 간선 추가하기 (최대 30개까지)
        int targetEdges = rand() % 11 + 20; // 20~30
        while (edges < targetEdges)
        {
            int u = rand() % n;
            int v = rand() % n;
            if (u != v && arr[u][v] == 0)
            {
                arr[u][v] = arr[v][u] = 1;
                edges++;
            }
        }
    }

    void printGraph()
    {
        cout << "    ";
        for (int j = 0; j < n; j++)
        {
            cout << setw(3) << j << " ";
        }
        cout << "\n    ";
        for (int j = 0; j < n; j++)
        {
            cout << "----";
        }
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            cout << setw(2) << i << " |";
            for (int j = 0; j < n; j++)
            {
                cout << setw(3) << arr[i][j] << " ";
            }
            cout << "\n";
        }
    }

    int getEdges() { return edges; }
    int getVertices() { return n; }
    int getWeight(int i, int j) { return arr[i][j]; }
};

#endif
