#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
	T value;
	Node<T> *left;
	Node<T> *right;
	public:
		Node<T>() {};
		Node<T>(T _value) { value = _value; };
		T getValue() { return value; };
		Node<T>* getNext() { return right; };
		Node<T>* getRight() { return right; };
		Node<T>* getPrevious() { return left; };
		Node<T>* getLeft() { return left; };
		void setNext(Node<T> *node) { right = node; };
		void setRight(Node<T> *node) { right = node; };
		void setPrevious(Node<T> *node) { left = node; };
		void setLeft(Node<T> *node) { left = node; };
};

#endif
