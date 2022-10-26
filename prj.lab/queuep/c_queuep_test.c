#include <queuep/queuep.h>
#include <iostream>
#include <memory>

QueueP::QueueP()
	: first(new Node(0, nullptr))
{
}

QueueP::QueueP(const QueueP& copy)
{
	first->val = copy.first->val;
	Node* temp_copy = copy.first.get();
	Node* last = nullptr;
	Node* temp = first.get();
	while ((temp_copy != nullptr)) {
		last = temp_copy;
		temp_copy = temp_copy->next.get();
		Node* nd = new Node(last->val, nullptr);
		temp->next = std::make_unique<Node>(nd);
		temp = temp->next.get();
	}
}

QueueP::QueueP(QueueP&& copy)
	: first(std::move(copy.first))
{
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
		*this = temp;
	}
	return *this;
}

QueueP& QueueP::operator=(QueueP&& rhs)
{
	if (this != &rhs) {
		QueueP temp = std::move(rhs);
		*this = temp;
	}
	return *this;
}

bool QueueP::isEmpty() const
{
	return first->next == nullptr;
}

const int& QueueP::top()
{
	return first->get_value();
}

void QueueP::push(const int& val)
{
	if (first->next == nullptr) {
		first = std::make_unique<Node>(new Node(val, nullptr));
		return;
	}

	Node* temp = first.get();
	Node* last = nullptr;
	while ((temp != nullptr) && (temp->get_value() < val)) {
		last = temp;
		temp = temp->next.get();
	}

	Node* nd = new Node(val, std::make_unique<Node>(temp));
	if (last != nullptr)
		last->next = std::make_unique<Node>(nd);
	else
		first = std::make_unique<Node>(nd);
	nd->next = std::make_unique<Node>(temp);
}

void QueueP::pop()
{
	if (isEmpty()) {
		return;
	}
	Node* temp = first->next.get();
	first = std::make_unique<Node>(temp);
}

int QueueP::Node::get_value()
{
	return val;
}
