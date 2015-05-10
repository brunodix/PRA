#ifndef DOUBLELIST_H
#define DOUBLELIST_H
#include "node.h"

using namespace std;

class DoubleList {
    int size;
    Node *first;
    Node *last;

public:
    DoubleList();
    ~DoubleList();
    void add(Node *node);
    //void remove(Node *node);
    //void show();
    Node* getByIndex(int index);
    void clear();

    int getSize();
};

#endif
