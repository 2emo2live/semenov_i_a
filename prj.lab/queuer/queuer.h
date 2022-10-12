#pragma once
#ifndef QUEUER_QUEUER_H_20221012
#define QUEUER_QUEUER_H_20221012

class QueueR {
public:
	QueueR();
	QueueR(const QueueR& copy);
	~QueueR();
	QueueR& operator=(const QueueR& rhs);

	bool isEmpty() const;

	int top();
	void push(const int &val);
	void pop();

private:
	struct Node {
		Node(const int& value, Node* nxt = nullptr)
			: val(value), next(nxt) {
		}

		int val;
		Node* next;

		int get_value();
	};

	Node* first;
	int _size = 0;
};
	
#endif