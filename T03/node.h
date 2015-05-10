#ifndef NODE_H
#define NODE_H

#include "stdlib.h"
#include <string>

using namespace std;

class Node {
    std::string value;
    Node *next;
    Node *prior;
public:
    Node(std::string value);
    void setValue(std::string value);
    std::string getValue();
    void setPrior(Node *_p) { prior = _p; };
    void setNext(Node *_n) { next = _n; };
    Node* getNext() { return next; };
    Node* getPrior() { return prior; };
};

#endif