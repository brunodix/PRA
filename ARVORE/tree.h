#ifndef TREE_H
#define TREE_H

#include <string>
#include "node.h"
#include <iostream>

using namespace std;

template <class NT>
class Tree {
	Node<NT> *root;
	static int preOrder(Node<NT> *node) {
		if (node != NULL) {
			cout << node->getValue();
			preOrder(node->getLeft());
			preOrder(node->getRight());
		}
	}
	static int inOrder(Node<NT> *node) {
		if (node != NULL) {
			inOrder(node->getLeft());
			cout << node->getValue();
			inOrder(node->getRight());
		}
	}
	static int postOrder(Node<NT> *node) {
		if (node != NULL) {
			postOrder(node->getLeft());
			postOrder(node->getRight());
			cout << node->getValue();
			
		}
	}

	public:
		void insert(NT value) {
			Node<NT>* newNode = new Node<NT>(value);
			Node<NT> *curNode, *prevNode;
			if (root == NULL) {
				root = newNode;
			} else {
				curNode = root;

				while (curNode) {
					prevNode = curNode;
					
					if (curNode->getValue() > newNode->getValue())
						curNode = curNode->getLeft();
					else
						curNode = curNode->getRight();
				}
				
				if (prevNode->getValue() > newNode->getValue())
					prevNode->setLeft(newNode);
				else
					prevNode->setRight(newNode);
			}
		};
		void traversePreOrder() {
			preOrder(root);
			cout << endl;
		}
		void traverseInOrder() {
			inOrder(root);
			cout << endl;
		}
		void traversePostOrder() {
			postOrder(root);
			cout << endl;
		}
};


#endif
