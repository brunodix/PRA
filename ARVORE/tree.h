#ifndef STACK_H
#define STACK_H

#include <string>
#include "node.h"

template <class NT>
class Tree {
	Node<NT> *root;
	public:
		void insert(Node<NT> *newNode) {
			Node<NT>* curNode, prevNode;
			if (root) {
				root = newNode;
			} else {
				curNode = root;

				while (curNode) {
					prevNode = curNode;
					
					if (curNode->value > newNode->value)
						curNode = curNode->getLeft();
					else
						curNode = curNode->getRight();
				}
				
				if (prevNode->value > newNode-> value)
					prevNode->setLeft(newNode);
				else
					prevNode->setRight(newNode);
			}
		};
};


#endif
