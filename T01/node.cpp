#include <stdlib.h>
#include "node.h"

using namespace std;

Node::Node(std::string value) {
    this->value = value;
    prior = NULL;
    next = NULL;
}

void Node::setValue(std::string value) {
    this->value = value;
}

std::string Node::getValue() {
    return this->value;
}