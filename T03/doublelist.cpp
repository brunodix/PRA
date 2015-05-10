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
        node->setPrior(NULL);
        node->setNext(NULL);
    } else {
        node->setPrior(last);
        last->setNext(node);
        last = node;
    }
}

Node *DoubleList::getByIndex(int index) {

    if (index >= size) {
        return NULL;
    } else {
        Node *ref = first;
        for (int i = 0; i < index; i++) {
            ref = ref->getNext();
        }
        return ref;
    }
}

void DoubleList::clear() {
}

int DoubleList::getSize() {
    return size;
}

DoubleList::~DoubleList() {
    do {
        Node *actual = last->getPrior();
        delete (last);
        last = actual;
    } while (last);
    first = NULL;
    last = NULL;
}
