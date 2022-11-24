#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

void input_f(std::istream& istrm) {
	int n = 0;
	istrm >> n;
	for (int i = 0; i < n; i += 1) {
		int idx = 0;
		istrm >> idx;
	}
}

void process_f(std::ostream& ostrm, vector<int>& input) {
	std::vector<int> as(200001, -1);
	for (int i = 0; i < n; i += 1)
		as[idx] = n - input[i] - 1;
	ostrm << std::distance(as.begin(),
		std::max_element(as.begin(), as.end()));
}