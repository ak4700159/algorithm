#ifndef __EDGE_H__
#define __EDGE_H__

class Edge
{
public:
    int start;
    int end;
    int weight;

public:
    Edge()
    {
        start = 0;
        end = 0;
        weight = 0;
    }
    Edge(int start, int end, int weight)
    {
        this->start = start;
        this->end = end;
        this->weight = weight;
    }
};

#endif