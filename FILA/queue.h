#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class QueueNode {
	T value;
	QueueNode<T> *next;
	///Referencia do ultimo para agilizar inserção
	QueueNode<T> *last;
	public:
	QueueNode(T);
};

template <class NT>
class Queue {
	QueueNode<NT> *first;
	public:
		void add(QueueNode<NT> *node);
		QueueNode<NT>* get();
};


#endif
