#include <chrono>
#include <random>
#include <string>
#include <sstream>
#include <functional>
#include "first.cpp"
#include "second.cpp"
#include<matplot/matplot.h>

std::mt19937 rng(172517);

double l = 128;

std::pair<double, double> measure_t(std::vector<int> input, std::function<std::pair<double, double> (std::stringstream&)> f) {
	std::stringstream io;
	for (int i = 0; i < input.size(); i++)
		io << std::to_string(input[i]);
	auto t = f(io);
	return t;
}

std::vector<int> generate_data(int n, int m, int M) {
	std::vector<int> data(m);
	std::vector<int> input(n);
	std::uniform_int_distribution<int> r_data(1, M);
	std::uniform_int_distribution<int> r_ind(0, m - 1);
	for (int i = 0; i < m; i++)
		data[i] = r_data(rng);
	for (int i = 0; i < n; i++)
		input[i] = data[r_ind(rng)];
	return input;
}

int main() {

	std::vector<double> x = { 1,2,3,4 };
	matplot::plot(x);
	matplot::save("barchart.jpg");
	/*
	std::function<std::pair<double, double>(std::stringstream&)> first_f = first;
	std::function<std::pair<double, double>(std::stringstream&)> second_f = second;
	std::vector<int> n(10);
	std::vector<std::vector<std::pair<double, double>>> t_f(10);
	std::vector<std::vector<std::pair<double, double>>> t_s(10);
	for (int i = 0; i < 10; i++) {
		std::uniform_int_distribution<int> n_i(1, 200000);
		n[i] = n_i(rng);
		int s = 0;
		for (double k = 1; k >= 1.0 / l; k / 2) {
			for (int p = 1; p <= l; p * 2) {
				int M = n[i] / p;
				int m = k * M;
				s += 1;
				t_f[i].push_back(std::make_pair(0, 0));
				t_s[i].push_back(std::make_pair(0, 0));
				for (int j = 0; j < 10; j++) {
					std::vector<int> inp(generate_data(n[i], m, M));
					auto t_fi = measure_t(inp, first_f);
					auto t_si = measure_t(inp, second_f);
					t_f[i][s].first += t_fi.first;
					t_f[i][s].second += t_fi.second;
					t_s[i][s].first += t_si.first;
					t_s[i][s].second += t_si.second;
				}
				t_f[i][s].first /= 10;
				t_f[i][s].second /= 10;
				t_s[i][s].first /= 10;
				t_f[i][s].second /= 10;
				std::cout << p << ' ' << k << '\n';
			}
		}
	}*/
}