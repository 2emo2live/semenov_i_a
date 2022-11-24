#include <iostream>
#include <vector>
#include <unordered_set>

void input_s(std::istream& istrm) {
	int n = 0;
	istrm >> n;
	std::vector<int> data(n, 0);
	for (int i = 0; i < n; i += 1) {
		istrm >> data[i];
	}
}

void process_s(std::ostream& ostrm, vector<int>& input) {
	std::unordered_set<int> unique;
	unique.reserve(200000);
	int idx_unique = n;
	for (int i = n - 1; 0 <= i; i -= 1) {
		if (!unique.contains(input[i])) {
			idx_unique = input[i];
			unique.insert(idx_unique);
		}
	}
	ostrm << idx_unique;
}