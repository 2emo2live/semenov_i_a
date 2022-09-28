#include <iostream>
#include <vector>

int main() {
	int n = 0;
	int d = 0;
	std::cin >> n;
	char m = 0;
	std::vector <int> del;
	std::vector <char> s;
	for (int i = 0; i < n; i++) {
		std::cin >> m;
		s.push_back(m);
	}
	for (int i = 2; i <= n; i++) {
		if (0 == (n % i)) {
			del.push_back(i - 1);
			d += 1;
		}
	}
	for (int i = 0; i < d; i++) {
		for (int j = 0; j <= (del[i] - 1) / 2; j++) {
			char ss = s[j];
			s[j] = s[del[i] - j];
			s[del[i] - j] = ss;
		}
//		for (int i = 0; i < n; i++) {
//			std::cout << s[i];
//		}
//		std::cout << std::endl;
	}
	for (int i = 0; i < n; i++) {
		std::cout << s[i];
	}
	return 0;
}