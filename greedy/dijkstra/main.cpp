#include <iostream>
#include "dijkstra.h"
#include "graph.h"
using namespace std;

int main(void)
{
    // 그래프 생성
    int n = 2000;
    Graph graph = Graph(n);
    graph.setConnectedGraph();
    // graph.printGraph();

    // 1번 vertex에 대한 최단 경로 탐색(1번 vertex는 1번째 인덱스를 가지는 vertex로 가정)
    Dijkstra* dijkstra = new Dijkstra(n, &graph); 
    dijkstra->searchShortestPath(1);
    for (int i = 0; i < n; i++)
    {
        int cost = dijkstra->printPath(i);
        cout << " (cost : " << cost << ")" << endl;
    } 
    return 0;
}
