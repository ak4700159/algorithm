#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <iomanip>
#include <queue>

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
        // 모든 노드가 연결되어 있는지 확인인
        for (int start = 0; start < n; ++start)
        {
            // 정방향 BFS
            if (!bfs(arr, start, n))
                return false;

            // 전치 그래프 생성
            int **transpose = new int *[n];
            for (int i = 0; i < n; i++)
            {
                transpose[i] = new int[n];
                for (int j = 0; j < n; j++)
                {
                    transpose[i][j] = arr[j][i];
                }
            }

            // 전치 BFS
            if (!bfs(transpose, start, n))
            {
                for (int i = 0; i < n; i++)
                    delete[] transpose[i];
                delete[] transpose;
                return false;
            }

            for (int i = 0; i < n; i++)
                delete[] transpose[i];
            delete[] transpose;
        }

        return true;
    }

    bool bfs(int **matrix, int start, int size)
    {
        bool *visited = new bool[size]{false};
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < size; i++)
            {
                if (matrix[cur][i] != INT_MAX && !visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        for (int i = 0; i < size; i++)
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
                arr[i][j] = INT_MAX;
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
            if (u == v || arr[u][v] != INT_MAX)
                continue;

            int weight = rand() % 100 + 1;
            arr[u][v] = weight; // 방향 그래프: 한 방향만 설정
            edges++;
            // cout << edges << " random edge : (" << u << "," << v << "), weightt: " << weight << endl;
        }
        // cout << "Number of Vertices : " << n << endl;
        // cout << "Number of Edges : " << edges << endl;
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
                if (arr[i][j] == INT_MAX)
                    cout << "INF ";
                else
                    cout << setw(3) << arr[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    int getWeight(int v, int u)
    {
        return arr[u][v];
    }
};

#endif
