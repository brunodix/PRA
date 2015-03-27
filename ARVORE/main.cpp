#include <stdlib.h>
#include "tree.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	Tree<int> *tree = new Tree<int>();
	tree->insert(8);
	std::cout << "First" << std::endl;
	tree->insert(3);
	tree->insert(1);
	tree->insert(6);
	tree->insert(5);
	tree->insert(4);
	tree->insert(9);
	tree->traversePreOrder();
	tree->traverseInOrder();
	tree->traversePostOrder();
}

