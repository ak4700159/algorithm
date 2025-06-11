#ifndef __TASK_H__
#define __TASK_H__

#include <iostream>
using namespace std;

class Task
{
private:
    int time;
    int machine;
    bool selected;

public:
    Task(int time) : time(time), machine(-1), selected(false) {}
    Task() : time(0), machine(-1), selected(false) {}

    // getter
    int getTime()
    {
        return time;
    }
    int getMachine()
    {
        return machine;
    }
    bool getSelected()
    {
        return selected;
    }

    // setter
    void setSelected(bool selected)
    {
        this->selected = selected;
    }
    void assignmentMachine(int machine)
    {
        this->machine = machine;
    }
};

#endif