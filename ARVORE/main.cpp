#include <stdlib.h>
#include "tree.h"

#include <string>
#include <iostream>

int main() {
	Tree<int> *tree = new Tree<int>();
	tree->insert(8);
	tree->insert(3);
	tree->insert(1);
	tree->insert(6);
	tree->insert(5);
	tree->insert(4);
	tree->insert(9);
}

