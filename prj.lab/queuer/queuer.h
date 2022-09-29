#pragma once
#ifndef RATIONAL_RATIONAL_H_20220309
#define RATIONAL_RATIONAL_H_20220309

class QueueR {
public:
	QueueR();

	bool isEmpty() const;
	int size() const;

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