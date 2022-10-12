#include <queuep/queuep.h>
#include <iostream>
#include <memory>

QueueP::QueueP()
	: first(new Node(0, nullptr))
{
}

/*QueueP::QueueP(const QueueP& copy)
{
	_size = copy._size;
	std::unique_ptr<Node> this_temp = std::move(first);
	std::unique_ptr<Node> temp = std::move(copy.first);
	this_temp->val = temp->val;
	temp = temp->next;
	for (int i = 1; i < _size; i++) {
		Node* nd = new Node(temp->val, nullptr);
		this_temp->next = nd;
		this_temp = this_temp->next;
		temp = temp->next;
	}
}

QueueP::~QueueP()
{
	while (!this->isEmpty())
		this->pop();
}

QueueP& QueueP::operator=(const QueueP& rhs)
{
	if (this != &rhs) {
		QueueP temp = rhs;
		first = temp.first;
		_size = temp._size;
	}
	return *this;
}

bool QueueP::isEmpty() const
{
	return _size == 0;
}

int QueueP::top()
{
	return first->get_value();
}

void QueueP::push(const int& val)
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

void QueueP::pop()
{
	if (_size == 0) {
		return;
	}
	Node* temp = first->next;
	delete first;
	first = temp;
	_size -= 1;
}

int QueueP::Node::get_value()
{
	return val;
}
*/