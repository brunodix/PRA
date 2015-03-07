#include <stdlib.h>
#include "node.h"

Node::Node(int value) {
    this->value = value;
    prior = NULL;
    next = NULL;
}

void Node::setValue(int value) {
    this->value = value;
}

int Node::getValue() {
    return this->value;
}