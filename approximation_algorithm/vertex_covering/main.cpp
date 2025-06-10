#include <iostream>
#include <ctime>
#include "graph.h"
#include "vertex_cover.h"

using namespace std;

/*
    1. Unweighted & Undirect graph를 생성하시오. (단, vertext는 10~20개, edge는 20~30개)
    2. 생성된 그래프를 다음 두가지 접근 방식을 사용하여 해결하시오.
        2-1. Vertex Priority Selection: 가장 많은 edge를 가지는 vertex를 우선 선택하는 방식
        2-2. Maximal Matching: disjoint edges(matching) 중심으로 선택하는 방식
    3. 1~2 과정을 10번 반복수행하시오.
    4. Vertex Priority Selection과 Maximal Matching 두 방식중 어떤 방식이 평균적으로 얼마만큼 우수한지 확인하시오.
*/

int main(void)
{
    srand(time(0));
    int totalSum1 = 0;
    int totalSum2 = 0;
    for (int i = 0; i < 10; i++)
    {
        // 그래프 생성 
        cout << "start for i = " << i << "!!" << endl;
        Graph* graph = new Graph();
        graph->setRandomGraph();

        // 첫번째 알고리즘 실행 : 정점 기준
        cout << "execVertexPrioritySelection result : " << endl;
        VertexCover cover1(graph);
        cover1.execVertexPrioritySelection();
        totalSum1 += cover1.getSelectedVertices();
        cout << "selected vertices = " << cover1.getSelectedVertices() << endl;

        // 두번째 알고리즘 실행 : 간선 기준
        // 최대 매칭 알고리즘 실행
        cout << "execMaximalMatching result : " << endl;
        VertexCover cover2(graph);
        cover2.execMaximalMatching();
        cout << "selected vertices = " << cover2.getSelectedVertices() << endl;
        totalSum2 += cover2.getSelectedVertices();
        cout << endl;
    }

    double average1 = ((double)totalSum1 / 10);
    double average2 = ((double)totalSum2 / 10);
    cout << "Vertex Priority Selection average : " << average1 << "(selected vertices)" << endl;
    cout << "Maximal Matching average : " << average2 << "(selected vertices)" << endl;
    if (average1 < average2)
    {
        cout << "Vertex Priority Selection selected less vertices than Maximal Matching : " << average2 - average1 << endl;
    }
    else if (average1 == average2)
    {
        cout << "two strategy are equal : " << average1 << endl;
    }
    else
    { 
        cout << "Maximal Matching selected less vertices than Vertex Priority Selection : " << average1 - average2 << endl;
    }

    return 0;
}
