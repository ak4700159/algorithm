#include <iostream>
#include "kruskal.h"
#include "graph.h"
using namespace std;

int main(void)
{
    Graph graph = Graph(10);
    graph.setConnectedGraph();

    Kruskal kruskal = Kruskal(graph);
    // true == 반드시 첫번째 간선 포함
    kruskal.searchMST(true);
    kruskal.printMST();
    return 0;
}
