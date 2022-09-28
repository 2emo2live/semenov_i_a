#include <iostream>
#include <vector>

int main() {
	int n = 0;
	int d = 0;
	std::cin >> n >> d;
	int m = 0;
	std::vector <int> numb;
	for (int i = 0; i < n; i++) {
		std::cin >> m;
		numb.push_back(m);
	}
	int ans = 2;
	for (int i = 1; i < n; i++) {
		int k = numb[i] - numb[i - 1];
		if (0 < k - 2 * d)
			ans += 2;
		else if (0 == k - 2 * d)
			ans += 1;
	}
	std::cout << ans;
	return 0;
}