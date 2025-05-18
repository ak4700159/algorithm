#ifndef __FLOYD_H__
#define __FLOYD_H__

#include <cstdlib>
#include <iomanip>
#include <climits>
#include <iostream>
#include "graph.h"

using namespace std;

class Folyd
{
private:
    // 플로이드 알고리즘 결과
    int **result;
    // 정점의 개수
    int n;
    // 이전에 방문한 정점에 대한 정보
    int **path;

public:
    Folyd(Graph *graph)
    {
        // 정점 개수
        this->n = graph->getVertices();

        // 결과 배열 초기화
        result = new int *[n];
        path = new int *[n];
        for (int i = 0; i < n; i++)
        {
            result[i] = new int[n];
            path[i] = new int[n];
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                {
                    result[i][j] = 0;
                    path[i][j] = i;
                    continue;
                }
                result[i][j] = graph->getWeight(i, j);
                // i -> j 로 가는 경로
                path[i][j] = j; // 초기 경로는 시작점으로 설정
            }
        }
    }

    ~Folyd()
    {
        for (int i = 0; i < n; i++)
        {
            delete[] result[i];
            delete[] path[i];
        }
        delete[] result;
        delete[] path;
    }

    // 모든 정점의 최단 거리 계산
    void searchShortestPaths()
    {
        // k: 거쳐가는 정점
        for (int k = 0; k < n; k++)
        {
            // i: 시작 정점
            for (int i = 0; i < n; i++)
            {
                // j: 도착 정점
                for (int j = 0; j < n; j++)
                {
                    // j와 k가 같다면 if문을 절대 만족하지 못하기 때문에 추가 X
                    if (i == j)
                        continue;
                    // k를 거쳐가는 경로가 더 짧은 경우 업데이트
                    if (result[i][k] != INT_MAX && result[k][j] != INT_MAX &&
                        result[i][k] + result[k][j] < result[i][j])
                    {
                        result[i][j] = result[i][k] + result[k][j];
                        path[i][j] = k; // 중간 정점 k를 저장
                        // cout << "Update path from " << i + 1 << " to " << j + 1 << " through " << k + 1 << " / cost : " << result[i][j] << endl;
                    }
                }
            }
        }
    }

    // start에서 end로 가는 경로 출력
    void printPath(int start, int end)
    {
        if (result[start][end] == INT_MAX)
        {
            cout << "No path exists from " << start + 1 << " to " << end + 1 << endl;
            return;
        }

        // cout << "Path from " << start + 1 << " to " << end + 1 << ": ";
        printPathRecursive(start, end);
        cout << endl;
        // cout << ", Distance: " << result[start][end] << endl;
    }

    // 여기서 중요한 점은 k 값을 선형적으로 접근하면서 업데이트하기 때문에
    // end 값을 k로 업데이트하면 된다.
    void printPathRecursive(int start, int end)
    {
        if (path[start][end] == end)
        {
            cout << start + 1 << " -> " << end + 1;
            return;
        }
        int k = path[start][end];
        printPathRecursive(start, k);
        cout << " -> " << end + 1;
    }

    void printMatrix()
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
                cout << setw(3) << result[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

#endif