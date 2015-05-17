#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
	BTree *btree = new BTree(2);
	btree->insert(8);
	btree->insert(3);
	btree->insert(1);
	btree->insert(6);
	btree->insert(5);
	btree->insert(4);
	btree->insert(9);
	btree->insert(56);
	btree->insert(78);
	btree->insert(34);
	btree->insert(87);
	btree->insert(23);
	btree->insert(90);
	btree->traverse();
	cout << endl;

	btree->remove(90);
	btree->traverse();
	cout << endl;
	btree->remove(56);
	btree->traverse();
	cout << endl;
	btree->remove(99);
	btree->traverse();
	cout << endl;
}

