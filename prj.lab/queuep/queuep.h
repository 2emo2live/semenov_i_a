#pragma once
#ifndef QUEUEP_QUEUEP_H_20221012
#define QUEUEP_QUEUEP_H_20221012

#include <memory>

class QueueP {
public:
	QueueP();
	QueueP(const QueueP& copy);
	~QueueP();
	QueueP& operator=(const QueueP& rhs);

	bool isEmpty() const;

	int top();
	void push(const int &val);
	void pop();

private:
	struct Node {
		Node(const int& value, std::unique_ptr<Node> nxt = nullptr)
			: val(value), next(std::move(nxt)) {
		}

		int val;
		std::unique_ptr<Node> next;

		int get_value();
	};

	std::unique_ptr<Node> first;
	int _size = 0;
};

#endif