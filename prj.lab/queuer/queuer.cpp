#include <queuer/queuer.h>
#include <iostream>

QueueR::QueueR()
	: first(nullptr)
{
}

bool QueueR::isEmpty() const
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
		return;
	}

	Node* temp = first;
	Node* last = nullptr;
	while ((temp != nullptr) && (temp->get_value() < val)) {
		last = temp;
		temp = temp->next;
	}

	Node* nd = new Node(val, temp);
	if (last != nullptr)
		last->next = nd;
	else
		first = nd;
	nd->next = temp;
}

void QueueR::pop()
{
	if (_size == 0) {
		return;
	}
	Node* temp = first->next;
	delete first;
	first = temp;
	_size -= 1;
}

int QueueR::Node::get_value()
{
	return val;
}
