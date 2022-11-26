#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>

std::pair<double, double> second(std::stringstream& strm) {
	auto start = std::chrono::system_clock::now();
	int n = 0;
	strm >> n;
	std::vector<int> data(n, 0);
	for (int i = 0; i < n; i += 1) {
		strm >> data[i];
	}
	auto end = std::chrono::system_clock::now();
	auto t_inp = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	start = std::chrono::system_clock::now();
	std::unordered_set<int> unique;
	unique.reserve(200000);
	int idx_unique = n;
	for (int i = n - 1; 0 <= i; i -= 1) {
		if (unique.find(data[i]) == unique.end()) {
			idx_unique = data[i];
			unique.insert(idx_unique);
		}
	}
	strm << idx_unique;
	end = std::chrono::system_clock::now();
	auto t_out = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	return std::make_pair(t_inp, t_out);
}
