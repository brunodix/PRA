#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
	BTree *btree = new BTree();
	btree->insert(8);
	btree->insert(3);
	btree->insert(1);
	btree->insert(6);
	btree->insert(5);
	btree->insert(4);
	btree->insert(9);
}

