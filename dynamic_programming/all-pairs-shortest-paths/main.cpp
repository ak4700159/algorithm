#include <iostream>
#include <ctime>
#include "dijkstra.h"
#include "floyd.h"

using namespace std;

clock_t execDijkstra();
clock_t execFloyd();

int main(void)
{
    clock_t dijkstraTime = execDijkstra();
    clock_t floydTime = execFloyd();
    // 총 걸린 시간
    cout << "[INFO] dijkstraTime = " << dijkstraTime << "ms" << endl;
    cout << "[INFO] floydTime = " << floydTime << "ms" << endl;
    return 0;
}

clock_t execDijkstra()
{
    clock_t totalTime = 0;
    // 정점의 개수를 10~20개까지 1씩 증가
    for (int i = 10; i <= 20; i++)
    {
        Graph graph = Graph(i);
        graph.setConnectedGraph();
        clock_t startTime = clock();
        cout << "[INFO] execDijkstra() START" << endl;
        Dijkstra dijkstra = Dijkstra(graph.getVertices(), &graph);
        // 각 정점에 대한 shortest path 구하기
        for (int n = 0; n < graph.getVertices(); n++)
        {
            cout << "[INFO] vertices=" << i << " shortest path about " << n + 1 << "th vertex" << endl;
            dijkstra.searchShortestPath(n);
            // 시작점으로부터 모든 정점에 대한 경로 출력 -> [n -> j 최단 경로]
            for (int j = 0; j < graph.getVertices(); j++)
            {
                if (n != j)
                {
                    dijkstra.printPath(j);
                    cout << endl;
                }
            }
            dijkstra.reset();
        }
        clock_t endTime = clock();
        clock_t elapsedTime = endTime - startTime;
        totalTime += elapsedTime;
        cout << "[INFO] vertices=" << i << " / total elapsed time " << elapsedTime << "ms" << endl << endl;
    }
    cout << endl << endl;
    return totalTime;
}

clock_t execFloyd()
{
    clock_t totalTime = 0;
    // 정점의 개수를 10~20개까지 1씩 증가
    for (int i = 10; i <= 20; i++)
    {
        Graph graph = Graph(i);
        graph.setConnectedGraph();
        clock_t startTime = clock();
        cout << "[INFO] execFloyd() START" << endl;
        Folyd floyd = Folyd(&graph);

        // Floyd 알고리즘 수행 및 matrix 완성
        floyd.searchShortestPaths();

        // 각 정점에 대한 shortest path 구하기
        for (int n = 0; n < graph.getVertices(); n++)
        {
            cout << "[INFO] vertices=" << i << " shortest path about " << n + 1 << "th vertex" << endl;
            // 시작점으로부터 모든 정점에 대한 경로 출력 -> [n -> j 최단 경로]
            for (int j = 0; j < graph.getVertices(); j++)
            {
                if (n != j)
                {
                    floyd.printPath(n, j);
                }
            }
        }
        clock_t endTime = clock();
        clock_t elapsedTime = endTime - startTime;
        totalTime += elapsedTime;
        cout << "[INFO] vertices=" << i << " / total elapsed time " << elapsedTime << "ms" << endl << endl;
    }
    cout << endl << endl;
    return totalTime;
}

/*
과제 내용 -> 시작점은 1번부터 시작.
====== Extended Version ======
<Dijkstra Algorithm의 시간측정>
1. random graph를 사용하여 임의의 connected directed weighted graph를 생성하시오. (vertex는 10개)
2. 1번 vertex를 시작점으로 하여 다른 모든점에 대한 shortest path 경로를 확인하시오.
3. 시작 vertex를 1,2,3...n개까지 바꾸어 가면서 최단경로를 확인하시오.
4. 2~3의 과정에 대한 시간을 측정하시오.
5. vertex 개수를 20까지 늘려가면서 위와 과정을 반복해보시오.

<Floyd Algorithm의 시간측정>
1. random graph를 사용하여 임의의 connected directed weighted graph를 생성하시오. (vertex는 10개)
2. 1에서 생성한 그래프를 Floyd 알고리즘 수행을 위한 matrix형태로 만드시오.
3. Floyd 알고리즘을 수행하여 all pair shortest path를 구하시오.(matrix를 완성하시오.)
4. 2~3번 과정에 대한 시간을 측정하시오.
5. vertex 개수를 20개까지 늘려가면서 위와 과정을 반복해보시오.
====== Advanced Version ======
path 정보를 입력하면 실제 경로를 추척할 수 있는 기능을 추가하시오.
예) 1,5 => 1에서 5로 가는 경로 출력 (1 -> 3-> 5)
*/