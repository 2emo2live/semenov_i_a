#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <queuer/queuer.h>



TEST_CASE("[queuer] - QueueR ctor") {
	QueueR a = QueueR();
	a.push(10);
	int b = a.top();
	std::cout << b << ' ';
	a.push(11);
	a.pop();
	std::cout << a.top() << std::endl;
	a.push(1);
	a.push(0);
	a.push(10);
	b = a.top();
	std::cout << b << ' ';
	a.pop();
	b = a.top();
	std::cout << b << ' ';
	a.pop();
	b = a.top();
	std::cout << b << ' ';
	a.pop();
	b = a.top();
	std::cout << b << ' ';
	a.pop();

}