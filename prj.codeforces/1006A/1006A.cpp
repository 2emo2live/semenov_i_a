#include <iostream>
#include <vector>

int main() {
	int n = 0;
	int m = 0;
	std::cin >> n;
	std::vector <int> numb;
	for (int i = 0; i < n; i++) {
		std::cin >> m;
		if (m % 2 == 0)
			m -= 1;
		numb.push_back(m);
	}
	for (int i = 0; i < n; i++) {
		std::cout << numb[i] << " ";
	}
	return 0;
}