#ifndef STACK_H
#define STACK_H

#include <string>
#include "stacknode.h"

template <class NT>
class Stack {
	StackNode<NT> *top;
	public:
		void push(StackNode<NT> *node);
		StackNode<NT>* pop();
};


#endif
