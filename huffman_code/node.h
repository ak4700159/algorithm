#ifndef __NODE_H__
#define __NODE_H__

class Node
{
public:
    Node(char s, int f) : symbol(s), frequcncy(f)
    {
        left = nullptr;
        right = nullptr;
    }
    char symbol;
    int frequcncy;
    Node *left;
    Node *right;
};

#endif