#ifndef DOUBLELIST_H
#define DOUBLELIST_H
#include "doublenode.h"

using namespace std;

class DoubleList {
    int size;
    DoubleNode *first;
    DoubleNode *last;

public:
    DoubleList();
    ~DoubleList();
    void add(DoubleNode *node);
    //void remove(DoubleNode *node);
    //void show();
    DoubleNode * getByIndex(int index);
    void clear();

    int getSize();
};

#endif
