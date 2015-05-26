#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <cstdlib>
#include <iostream>

using namespace std;

template <class T>
class  Node {
    T value;
    Node *next;
    Node *prior;
public:
    Node(T value) {
        next = NULL;
        prior = NULL;
        setValue(value);
    };
    void setValue(T value){
        this->value = value;
    };
    T getValue(){
        return value;
    };
    void setPrior(Node<T> *_p) { prior = _p; };
    void setNext(Node<T> *_n) { next = _n; };
    Node<T>* getNext() { return next; };
    Node<T>* getPrior() { return prior; };
};

template <class NT>
class DoubleList {
    int size;
    Node<NT> *first;
    Node<NT> *last;

public:
    DoubleList(){
        size = 0;
        first = NULL;
        last = NULL;
    };
    ~DoubleList(){
        do {
            Node<NT> *actual = last->getPrior();
            delete (last);
            last = actual;
        } while (last);
        first = NULL;
        last = NULL;
    };
    void add(Node<NT> *node) {
        size++;
        if (!first) {
            first = node;
            last = node;
            node->setPrior(NULL);
            node->setNext(NULL);
        } else {
            node->setPrior(last);
            last->setNext(node);
            last = node;
        }
    };
    //void remove(Node *node);
    //void show();
    Node<NT>* getByIndex(int index){
        if (index >= size) {
            return NULL;
        } else {
            Node<NT> *ref = first;
            for (int i = 0; i < index; i++) {
                ref = ref->getNext();
            }
            return ref;
        }
    };

    int getSize() {
        return size;
    };

    void clear() {
        Node<NT> *node = first;
        while (node != NULL) {
            Node<NT> *nTemp = node;
            node = node->getNext();
            delete(nTemp);
        }
    };

};

#endif
