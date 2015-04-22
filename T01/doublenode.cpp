#include <stdlib.h>
#include "doublenode.h"

using namespace std;

DoubleNode::DoubleNode(std::string value) {
    this->value = value;
    prior = NULL;
    next = NULL;
}

void DoubleNode::setValue(std::string value) {
    this->value = value;
}

std::string DoubleNode::getValue() {
    return this->value;
}