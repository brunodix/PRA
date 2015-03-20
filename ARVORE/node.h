#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
	T value;
	Node<T> *left;
	Node<T> *right;
	public:
		Node<T> getNext() { return right; };
		Node<T> getRight() { return right; };
		Node<T> getPrevious() { return left; };
		Node<T> getLeft() { return left; };
		void setNext(Node<T> node) { right = node; };
		Node<T> setRight(Node<T> node) { right = node; };
		Node<T> setPrevious(Node<T> node) { left = node; };
		Node<T> setLeft(Node<T> node) { left = node; };
};

#endif
