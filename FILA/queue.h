#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class QueueNode {
	T value;
	QueueNode<T> *next;
	public:
	QueueNode(T _value) { value = _value; };
	void setNext(QueueNode<T> *node) { next = node;  };
	QueueNode<T>* getNext() { return next;  };
};

template <class NT>
class Queue {
	QueueNode<NT> *first;
	///Referencia do ultimo para agilizar inserção
	QueueNode<NT> *last;
	public:
		void queue(QueueNode<NT> *node) {
			if (first) {
				last->setNext(node);
				last = node;
			}

		};
		QueueNode<NT>* dequeue() {};
};

#endif
