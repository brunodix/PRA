#ifndef NODE_H
#define NODE_H

class Node {
    int value;
    Node *next;
    Node *prior;
public:
    Node(int value);
    void setValue(int value);
    int getValue();
    void setPrior(Node *_p) { prior = _p; };
    void setNext(Node *_n) { next = _n; };
    Node* getNext() { return next; };
    Node* getPrior() { return prior; };
};

#endif