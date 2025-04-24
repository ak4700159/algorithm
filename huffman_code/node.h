#ifndef __NODE_H__
#define __NODE_H__

#include "setting.h"
#include <iostream>

using namespace std;

class Node
{
public:
    Node() {
        frequcncy = MAX_INT;
    }
    Node(char s, int f) : symbol(s), frequcncy(f)
    {
        left = nullptr;
        right = nullptr;
    }
    Node(int f, Node* left, Node* right) : frequcncy(f), left(left), right(right) {}
    char symbol;
    int frequcncy;
    Node *left;
    Node *right;

    void printNode() {
        if (isprint(symbol))
        {
            cout << symbol << " / " << frequcncy << endl;
        }
        else
        {
            cout << getControlCharName(symbol) << " / " << frequcncy << endl;
        }
    }
};


#endif