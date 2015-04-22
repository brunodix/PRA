#ifndef DOUBLE_NODE_H
#define DOUBLE_NODE_H

#include "stdlib.h"
#include <string>

using namespace std;

class DoubleNode {
    std::string value;
    DoubleNode *next;
    DoubleNode *prior;
public:
    DoubleNode(std::string value);
    void setValue(std::string value);
    std::string getValue();
    void setPrior(DoubleNode *_p) { prior = _p; };
    void setNext(DoubleNode *_n) { next = _n; };
    DoubleNode * getNext() { return next; };
    DoubleNode * getPrior() { return prior; };
};

#endif