#ifndef __VERTEX_COVER_H__
#define __VERTEX_COVER_H__

#include <iostream>
#include "graph.h"

using namespace std;

// 주어진 그래프에서 최소한의 정점을 선택하여
// 전체 간선을 커버하는 경우를 탐색
class VertexCover
{
private:
    Graph graph;
    bool *selected;

public:
    VertexCover(Graph *graph)
    {
        this->graph = *graph; // Graph 복사
        int n = this->graph.getVertices();
        this->selected = new bool[n];
        for (int i = 0; i < n; ++i)
            selected[i] = false;
    }

    ~VertexCover()
    {
        delete[] selected;
    }

    // 선택된 정점 전부 초기화
    void reset()
    {
        for (int i = 0; i < graph.getVertices(); i++)
        {
            selected[i] = false;
        }
    }

    void printSelectedVertices()
    {
        for (int i = 0; i < graph.getVertices(); i++)
        {
            if (selected[i])
            {
                cout << "selected vertex : " << i << endl;
            }
        }
    }

    int getSelectedVertices()
    {
        int num = 0;
        for (int i = 0; i < graph.getVertices(); i++)
        {
            if (selected[i])
                num++;
        }
        return num;
    }

    // Vertex Priority Selection 방식으로 vertex covering 알고리즘 실행
    // 해당 알고리즘은 정점
    void execVertexPrioritySelection()
    {
        // graph.printGraph();
        int n = graph.getVertices();
        // 각 정점마다 연결된 간선 수 (degree) 계산
        int *degree = new int[n]{0};
        bool **covered = new bool *[n];
        for (int i = 0; i < n; ++i)
        {
            covered[i] = new bool[n];
            for (int j = 0; j < n; ++j)
            {
                // 그래프는 무방향 그래프이기 때문에 0이 아니면 단순히 간선이 있음을 의미
                if (graph.getWeight(i, j) != 0)
                {
                    degree[i]++;
                    covered[i][j] = true;
                }
                else
                {
                    covered[i][j] = false;
                }
            }
        }

        // 모든 간선을 커버할 때까지 무한 loop문
        while (true)
        {
            // 가장 degree가 높은 정점 선택
            int maxDegree = -1, maxVertex = -1;
            for (int i = 0; i < n; ++i)
            {
                // 차수가 높고(연결된 간선이 많은) 선택되지 않은 정점 선택
                if (!selected[i] && degree[i] > maxDegree)
                {
                    maxDegree = degree[i];
                    maxVertex = i;
                }
            }

            if (maxDegree == 0)
                break; // 모든 간선이 커버됨

            // 해당 정점 선택
            selected[maxVertex] = true;

            // 해당 정점과 연결된 모든 간선 제거
            for (int j = 0; j < n; ++j)
            {
                // (maxVertex, j) 간선이 있는 경우!
                if (covered[maxVertex][j])
                {
                    covered[maxVertex][j] = false;
                    covered[j][maxVertex] = false;
                    // 정점 j 입장에서도 똑같이 차수가 줄어듬
                    degree[j]--;
                }
            }
            degree[maxVertex] = 0;
        }

        delete[] degree;
        for (int i = 0; i < n; ++i)
            delete[] covered[i];
        delete[] covered;
    }

    // Maximal Matching: disjoint edges(matching) 방식으로 vertex 알고리즘 실행
    void execMaximalMatching()
    {
        // graph.printGraph();
        int n = graph.getVertices();
        // E′: 아직 커버되지 않은 간선 목록  -> coverd 안의 모든 값이 false로 바뀌면 모든 간선이 커버되었음을 의미
        bool **covered = new bool *[n];
        for (int i = 0; i < n; i++)
        {
            covered[i] = new bool[n];
            for (int j = 0; j < n; j++)
            {
                covered[i][j] = (graph.getWeight(i, j) != 0); // 간선이 존재하면 true
            }
        }

        // 단순히 순차적으로 커버되지 않은 간선을 선택
        for (int u = 0; u < n; ++u)
        {
            for (int v = u + 1; v < n; ++v)
            {
                // 커버되지 않은 간선을 선택
                if (covered[u][v])
                {
                    if (selected[u] || selected[v])
                    {
                        cout << "error" << endl;
                        exit(1);
                    }
                    // E(u,v)을 커버할 정점으로 u, v정점이 선택
                    selected[u] = true;
                    selected[v] = true;

                    // u 또는 v와 연결된 모든 간선 제거
                    for (int i = 0; i < n; ++i)
                    {
                        // 정점 u와 연결된 간선 제거
                        covered[u][i] = false;
                        covered[i][u] = false;
                        // 정점 v와 연결된 간선 제거
                        covered[v][i] = false;
                        covered[i][v] = false;
                    }
                }
            }
        }

        // 메모리 해제
        for (int i = 0; i < n; i++)
            delete[] covered[i];
        delete[] covered;
    }
};

#endif