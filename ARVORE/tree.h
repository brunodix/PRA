#ifndef TREE_H
#define TREE_H

#include <string>
#include "node.h"
#include <iostream>

template <class NT>
class Tree {
	Node<NT> *root;
	public:
		void insert(NT value) {
			Node<NT>* newNode = new Node<NT>(value);
			Node<NT> *curNode, *prevNode;
			if (root) {
				root = newNode;
			} else {
				curNode = root;
				std::cout << "Root Value" << root->getValue() << std::endl;
				int cont = 0;

				while (curNode) {
					cont++;
					prevNode = curNode;
					
					if (curNode->getValue() > newNode->getValue())
						curNode = curNode->getLeft();
					else
						curNode = curNode->getRight();
				}
				std::cout << cont << std::endl;
				
				if (prevNode->getValue() > newNode->getValue())
					prevNode->setLeft(newNode);
				else
					prevNode->setRight(newNode);
			}
		};
};


#endif
