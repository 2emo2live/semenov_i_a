#include <queuer/queuer.h>

QueueR::QueueR()
	: first(nullptr), last(nullptr)
{
}

bool QueueR::empty() const
{
	return _size == 0;
}

int QueueR::size() const
{
	return _size;
}

int QueueR::top()
{
	return first->get_value();
}

void QueueR::push(const int& val)
{
	_size += 1;
	if (_size == 1) {
		Node* nd = new Node(val, nullptr);
		first = nd;
		last = nd;
		return;
	}

	if (first->get_value() > val) {
		Node* nd = new Node(val, first);
		first = nd;
		return;
	}

	Node* temp = first;
	while (temp->get_value() > val) {
		temp = temp->next;
	}

	Node* nd = new Node(val, temp);
	last->next = nd;
	last = nd;
}

void QueueR::pop()
{
	if (first == last) {
		delete first;
		first = nullptr;
		last = nullptr;
		return;
	}
	Node* temp = first->next;
	delete first;
	first = temp;
}



int Node::get_value()
{
	return val;
}
