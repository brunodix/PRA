
#include "queue.h"

int main() {
	Queue<int> *stk = new Queue<int>();
	QueueNode<int> *node = new QueueNode<int>(4);
	stk->add(node);

	return 0;
}
