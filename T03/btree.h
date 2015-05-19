#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include "constants.h"

using namespace std;

class Key {
	private:
		Student *student = NULL;
	public:
		Key(Student *student) {
			this->student = student;
		};

		long traverse() {
			return student->getEnrollNumber();
		}
		void init() {
			student = NULL;
		};
		Student *getStudent(){ return student; };
};

class BTreeNode {
    Key **keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    BTreeNode **child; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
	int (*fComparator)(const void *, const void *);

public:
    BTreeNode(int _t, bool _leaf, int comparator(const void *, const void *));   // Constructor

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(Key *k);

    // A utility function to split the child y of this node. i is index of y in
    // child array C[].  The Child y must be full when this function is called
    void splitChild(int i, BTreeNode *y);

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();

	void traverse(FILE *file);

	void clear() {
		int i;
		for (i = 0; i < n; i++) {
			if (leaf == false) {
				child[i]->clear();
				delete child[i];
			}
			delete keys[i];
		}
		if (leaf == false) {
			child[i]->clear();
			delete child[i];
		}

	};

    // Make BTree friend of this so that we can access private members of this
    // class in BTree functions
    friend class BTree;

//	int getPred(int idx);
//
//	void removeFromLeaf(int idx);
//
//	void remove(int k);
//
//	int findKey(int k);
//
//	void removeFromNonLeaf(int idx);
//
//	int getSucc(int idx);
//
//	void merge(int idx);
//
//	void borrowFromPrev(int idx);
//
//	void borrowFromNext(int idx);
//
//	void fill(int idx);
};

// A BTree
class BTree {
    BTreeNode *root; // Pointer to root node
    int t;  // Minimum degree
	int (*fComparator)(const void *, const void *);

public:
    // Constructor (Initializes tree as empty)
    BTree(int _t, int comparator(const void *, const void *)) {
        root = NULL;
        t = _t;
        fComparator = comparator;
    }

    // function to traverse the tree
    void traverse() { if (root != NULL) root->traverse(); }

	// function to traverse the tree
	void traverse(FILE *f) { if (root != NULL) root->traverse(f); }

    // The main function that inserts a new key in this B-Tree
    void insert(Key *k);

    void remove(int k);

	friend class BTreeNode;

	void clear() {if (root != NULL) root->clear(); delete root; }
};

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int t1, bool leaf1, int comparator(const void *, const void *)) {
    // Copy the given minimum degree and leaf property
    t = t1;
    leaf = leaf1;

    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new Key *[2 * t - 1];
    child = new BTreeNode *[2 * t];
	for (int i = 0; i < 2*t-1; i++) {
		keys[i]=NULL;
	}

    // Initialize the number of keys as 0
    n = 0;
	fComparator = comparator;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse(FILE *file) {
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++) {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false) {
			child[i]->traverse(file);
			long value = keys[i]->traverse();
			fwrite(&value, LONG_SIZE, 1, file);
		}
    }

    // Print the subtree rooted with last child
    if (leaf == false) {
        child[i]->traverse(file);
	}
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse() {
	// There are n keys and n+1 children, travers through n keys
	// and first n children
	int i;
	for (i = 0; i < n; i++) {
		// If this is not leaf, then before printing key[i],
		// traverse the subtree rooted with child C[i].
		if (leaf == false)
			child[i]->traverse();
		cout << " " << keys[i]->traverse();
	}

	// Print the subtree rooted with last child
	if (leaf == false)
		child[i]->traverse();
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(Key *k) {
    // If tree is empty
    if (root == NULL) {
        // Allocate memory for root
        root = new BTreeNode(t, true, fComparator);
        root->keys[0] = k;  // Insert key
        root->n = 1;  // Update number of keys in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2 * t - 1) {
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(t, false, fComparator);

            // Make old root as child of new root
            s->child[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);

            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
			//if (s->keys[0] < k)
            if (fComparator(k, s->keys[0]) > 0 )
                i++;
            s->child[i]->insertNonFull(k);

            // Change root
            root = s;
        }
        else  // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y) {
    // Create a new node which is going to store (t-1) keys
    // of y
    BTreeNode *z = new BTreeNode(y->t, y->leaf, fComparator);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    // Copy the last t children of y to z
    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->child[j] = y->child[j + t];
    }

    // Reduce the number of keys in y
    y->n = t - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i + 1; j--)
        child[j + 1] = child[j];

    // Link the new child to this node
    child[i + 1] = z;

    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    // Copy the middle key of y to this node
    keys[i] = y->keys[t - 1];

    // Increment count of keys in this node
    n = n + 1;
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(Key *k) {
    // Initialize index as index of rightmost element
    int i = n - 1;

    // If this is a leaf node
    if (leaf == true) {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
		//while (i >= 0 && keys[i] > k)
        while (i >= 0 && fComparator(keys[i], k) > 0) {
            keys[i + 1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i + 1] = k;
        n = n + 1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && fComparator(keys[i], k) > 0)
            i--;

        // See if the found child is full
        if (child[i + 1]->n == 2 * t - 1) {
            // If the child is full, then split it
            splitChild(i + 1, child[i + 1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (keys[i + 1] < k)
                i++;
        }
        child[i + 1]->insertNonFull(k);
    }
}

/*
// A utility function that returns the index of the first key that is
// greater than or equal to k
int BTreeNode::findKey(int k)
{
	int idx=0;
	while (idx<n && keys[idx] < k)
		++idx;
	return idx;
}

// A function to remove the key k from the sub-tree rooted with this node
void BTreeNode::remove(int k)
{
	int idx = findKey(k);

	// The key to be removed is present in this node
	if (idx < n && keys[idx] == k)
	{

		// If the node is a leaf node - removeFromLeaf is called
		// Otherwise, removeFromNonLeaf function is called
		if (leaf)
			removeFromLeaf(idx);
		else
			removeFromNonLeaf(idx);
	}
	else
	{

		// If this node is a leaf node, then the key is not present in tree
		if (leaf)
		{
			cout << "The key "<< k <<" is does not exist in the tree\n";
			return;
		}

		// The key to be removed is present in the sub-tree rooted with this node
		// The flag indicates whether the key is present in the sub-tree rooted
		// with the last child of this node
		bool flag = ( (idx==n)? true : false );

		// If the child where the key is supposed to exist has less that t keys,
		// we fill that child
		if (child[idx]->n < t)
			fill(idx);

		// If the last child has been merged, it must have merged with the previous
		// child and so we recurse on the (idx-1)th child. Else, we recurse on the
		// (idx)th child which now has atleast t keys
		if (flag && idx > n)
			child[idx-1]->remove(k);
		else
			child[idx]->remove(k);
	}
	return;
}

// A function to fill child C[idx] which has less than t-1 keys
void BTreeNode::fill(int idx)
{

	// If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
	// from that child
	if (idx!=0 && child[idx-1]->n>=t)
		borrowFromPrev(idx);

		// If the next child(C[idx+1]) has more than t-1 keys, borrow a key
		// from that child
	else if (idx!=n && child[idx+1]->n>=t)
		borrowFromNext(idx);

		// Merge C[idx] with its sibling
		// If C[idx] is the last child, merge it with with its previous sibling
		// Otherwise merge it with its next sibling
	else
	{
		if (idx != n)
			merge(idx);
		else
			merge(idx-1);
	}
	return;
}

// A function to borrow a key from C[idx-1] and insert it
// into C[idx]
void BTreeNode::borrowFromPrev(int idx)
{

	BTreeNode *childb= child[idx];
	BTreeNode *sibling= child[idx-1];

	// The last key from C[idx-1] goes up to the parent and key[idx-1]
	// from parent is inserted as the first key in C[idx]. Thus, the  loses
	// sibling one key and child gains one key

	// Moving all key in C[idx] one step ahead
	for (int i=childb->n-1; i>=0; --i)
		childb->keys[i+1] = childb->keys[i];

	// If C[idx] is not a leaf, move all its child pointers one step ahead
	if (!childb->leaf)
	{
		for(int i=childb->n; i>=0; --i)
			childb->child[i+1] = childb->child[i];
	}

	// Setting child's first key equal to keys[idx-1] from the current node
	childb->keys[0] = keys[idx-1];

	// Moving sibling's last child as C[idx]'s first child
	if (!leaf)
		childb->child[0] = sibling->child[sibling->n];

	// Moving the key from the sibling to the parent
	// This reduces the number of keys in the sibling
	keys[idx-1] = sibling->keys[sibling->n-1];

	childb->n += 1;
	sibling->n -= 1;

	return;
}

// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
void BTreeNode::borrowFromNext(int idx)
{

	BTreeNode *childb=child[idx];
	BTreeNode *sibling=child[idx+1];

	// keys[idx] is inserted as the last key in C[idx]
	childb->keys[(childb->n)] = keys[idx];

	// Sibling's first child is inserted as the last child
	// into C[idx]
	if (!(childb->leaf))
		childb->child[(childb->n)+1] = sibling->child[0];

	//The first key from sibling is inserted into keys[idx]
	keys[idx] = sibling->keys[0];

	// Moving all keys in sibling one step behind
	for (int i=1; i<sibling->n; ++i)
		sibling->keys[i-1] = sibling->keys[i];

	// Moving the child pointers one step behind
	if (!sibling->leaf)
	{
		for(int i=1; i<=sibling->n; ++i)
			sibling->child[i-1] = sibling->child[i];
	}

	// Increasing and decreasing the key count of C[idx] and C[idx+1]
	// respectively
	childb->n += 1;
	sibling->n -= 1;

	return;
}

// A function to remove the idx-th key from this node - which is a leaf node
void BTreeNode::removeFromLeaf (int idx)
{

	// Move all the keys after the idx-th pos one place backward
	for (int i=idx+1; i<n; ++i)
		keys[i-1] = keys[i];

	// Reduce the count of keys
	n--;

	return;
}

// A function to get predecessor of keys[idx]
int BTreeNode::getPred(int idx)
{
	// Keep moving to the right most node until we reach a leaf
	BTreeNode *cur=child[idx];
	while (!cur->leaf)
		cur = cur->child[cur->n];

	// Return the last key of the leaf
	return cur->keys[cur->n-1];
}

int BTreeNode::getSucc(int idx)
{

	// Keep moving the left most node starting from C[idx+1] until we reach a leaf
	BTreeNode *cur = child[idx+1];
	while (!cur->leaf)
		cur = cur->child[0];

	// Return the first key of the leaf
	return cur->keys[0];
}

// A function to remove the idx-th key from this node - which is a non-leaf node
void BTreeNode::removeFromNonLeaf(int idx)
{

	int k = keys[idx];

	// If the child that precedes k (C[idx]) has atleast t keys,
	// find the predecessor 'pred' of k in the subtree rooted at
	// C[idx]. Replace k by pred. Recursively delete pred
	// in C[idx]
	if (child[idx]->n >= t)
	{
		int pred = getPred(idx);
		keys[idx] = pred;
		child[idx]->remove(pred);
	}

		// If the child C[idx] has less that t keys, examine C[idx+1].
		// If C[idx+1] has atleast t keys, find the successor 'succ' of k in
		// the subtree rooted at C[idx+1]
		// Replace k by succ
		// Recursively delete succ in C[idx+1]
	else if  (child[idx+1]->n >= t)
	{
		int succ = getSucc(idx);
		keys[idx] = succ;
		child[idx+1]->remove(succ);
	}

		// If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
		// into C[idx]
		// Now C[idx] contains 2t-1 keys
		// Free C[idx+1] and recursively delete k from C[idx]
	else
	{
		merge(idx);
		child[idx]->remove(k);
	}
	return;
}

// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
void BTreeNode::merge(int idx)
{
	BTreeNode *childb = child[idx];
	BTreeNode *sibling = child[idx+1];

	// Pulling a key from the current node and inserting it into (t-1)th
	// position of C[idx]
	childb->keys[t-1] = keys[idx];

	// Copying the keys from C[idx+1] to C[idx] at the end
	for (int i=0; i<sibling->n; ++i)
		childb->keys[i+t] = sibling->keys[i];

	// Copying the child pointers from C[idx+1] to C[idx]
	if (!childb->leaf)
	{
		for(int i=0; i<=sibling->n; ++i)
			childb->child[i+t] = sibling->child[i];
	}

	// Moving all keys after idx in the current node one step before -
	// to fill the gap created by moving keys[idx] to C[idx]
	for (int i=idx+1; i<n; ++i)
		keys[i-1] = keys[i];

	// Moving the child pointers after (idx+1) in the current node one
	// step before
	for (int i=idx+2; i<=n; ++i)
		child[i-1] = child[i];

	// Updating the key count of child and the current node
	childb->n += sibling->n+1;
	n--;

	// Freeing the memory occupied by sibling
	delete(sibling);
	return;
}



//	2. Caso o elemento esteja em uma p´agina interna, o elemento deve ser
//	substitu´ıdo pelo seu sucessor (ou antecessor) na ´arvore (percurso em
//	ordem) = processo denominado doa¸c˜ao
//	No caso de doa¸c˜ao:
//	2.1 se a p´agina doadora tiver m > n, basta doar um elemento
//	2.2 se a p´agina doadora tiver m = n:
//	2.2.1 se alguma das p´aginas irm˜as tiver m > n: redistribui¸c˜ao de elementos entre
//	p´aginas irm˜as (rota¸c˜ao da sub-´arvore)
//	2.2.2 caso contr´ario: concatena¸c˜ao recursiva entre p´aginas irm˜as (join)

void BTree::remove(int k)
{
	if (!root)
	{
		cout << "The tree is empty\n";
		return;
	}

	// Call the remove function for root
	root->remove(k);

	// If the root node has 0 keys, make its first child as the new root
	//  if it has a child, otherwise set root as NULL
	if (root->n==0)
	{
		BTreeNode *tmp = root;
		if (root->leaf)
			root = NULL;
		else
			root = root->child[0];

		// Free the old root
		delete tmp;
	}
	return;
}*/

#endif //BTREE_H

