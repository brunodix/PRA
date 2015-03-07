#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <strings.h>
#include <functional>
#include "doublelist.h"

DoubleList::DoubleList() {
    size = 0;
   first = NULL;
    last = NULL;
}

void DoubleList::add(Node *node) {
    size++;
    if (!first) {
        first = node;
        last = node;
    } else {
        last->setNext(node);
        last = node;
    }
}

Node* DoubleList::getByIndex(int index){

    if (index >= size) {
        return NULL;
    } else {
        Node * ref = first;
        for (int i = 0; i<index; i++) {
            ref = ref->getNext();
        }
        return ref;
    }
}

void DoubleList::clear() {
    Node * ref = first;
    while (ref) {
        Node * actual = ref;
        ref = actual->getNext();
        delete (actual);
    }
    first = NULL;
}

int DoubleList::getSize() {
    return size;
}
