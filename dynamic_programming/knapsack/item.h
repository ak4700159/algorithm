#ifndef __ITEM_H__
#define __ITEM_H__

class Item{
private:
    int cost;
    int weight;
public:
    Item(int c, int w) : cost(c), weight(w) { }
    Item() { };
    int getCost() { return cost; }
    int getWeight() { return weight; };
};

#endif