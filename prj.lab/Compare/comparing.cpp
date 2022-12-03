#include <chrono>
#include <random>
#include <string>
#include <sstream>
#include <functional>
#include "first.cpp"
#include "second.cpp"
#include "gen_report.cpp"
#include <matplot/matplot.h>
#include <algorithm>
#include <hpdf.h>

std::mt19937 rng(172517);

double l = 16;
int acc = 3;
int n_size = 10;

std::pair<double, double> measure_t(std::vector<int> input, std::function<std::pair<double, double> (std::stringstream&)> f) {
	std::stringstream io;
	io << std::to_string(input.size());
	io << '\n';
	for (int i = 0; i < input.size(); i++) {
		io << std::to_string(input[i]);
		io << ' ';
	}
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

	/*std::function<std::pair<double, double>(std::stringstream&)> first_f = first;
	std::function<std::pair<double, double>(std::stringstream&)> second_f = second;
	std::vector<int> n(n_size);
	std::vector<std::vector<std::pair<double, double>>> t_f(n_size);
	std::vector<std::vector<std::pair<double, double>>> t_s(n_size);
	int sc = 20;
	for (int i = 0; i < n_size; i++) {
		std::uniform_int_distribution<int> n_i(1, sc);
		n[i] = n_i(rng);
		if (sc <= 20000)
			sc *= 10;
	}
	std::sort(n.begin(), n.end());
	for (int i = 0; i < n_size; i++) {
		int s = -1;
		for (double k = 1; k >= 1.0 / l; k /= 2) {
			for (int p = 1; p <= l; p *= 2) {
				int M = std::max(n[i] / p, 1);
				int m = std::max((int)k * M, 1);
				s += 1;
				t_f[i].push_back(std::make_pair(0, 0));
				t_s[i].push_back(std::make_pair(0, 0));
				for (int j = 0; j < acc; j++) {
					//std::cout << p << ' ' << k << ' ' << s << ' ' << j << '\n';
					std::vector<int> inp(generate_data(n[i], m, M));
					auto t_fi = measure_t(inp, first_f);
					auto t_si = measure_t(inp, second_f);
					t_f[i][s].first += t_fi.first;
					t_f[i][s].second += t_fi.second;
					t_s[i][s].first += t_si.first;
					t_s[i][s].second += t_si.second;
				}
				t_f[i][s].first /= acc;
				t_f[i][s].second /= acc;
				t_s[i][s].first /= acc;
				t_f[i][s].second /= acc;
			}
		}
	}
	std::vector<double> f_inp_gr(n_size);
	std::vector<double> f_pr_gr(n_size);
	std::vector<double> s_inp_gr(n_size);
	std::vector<double> s_pr_gr(n_size);
	std::vector<int> steps{0, 4, 16, 24};
	//p = 2^(st%5), k = 2^(-(st/5))
	for (int st: steps) {
		for (int i = 0; i < n_size; i++) {
			f_inp_gr[i] = t_f[i][st].first;
			f_pr_gr[i] = t_f[i][st].second;
			s_inp_gr[i] = t_s[i][st].first;
			s_pr_gr[i] = t_s[i][st].second;
		}
		double k = pow(2, -(int)(st/5));
		int p = pow(2, (st % 5));
		matplot::plot(n, f_inp_gr, n, s_inp_gr);
		matplot::legend({ "first solution", "second solution" });
		matplot::title("Input with k = " + std::to_string(round(k*10000)/10000) + " and p = " + std::to_string(p));
		matplot::xlabel("n");
		matplot::ylabel("time");
		matplot::save("input" + std::to_string(st) + ".jpg");

		matplot::plot(n, f_pr_gr, n, s_pr_gr);
		matplot::legend({ "first solution", "second solution" });
		matplot::title("Process with k = " + std::to_string(round(k * 10000) / 10000) + " and p = " + std::to_string(p));
		matplot::xlabel("n");
		matplot::ylabel("time");
		matplot::save("process" + std::to_string(st) + ".jpg");
	}*/
	
	std::vector<int> steps{ 0, 4, 16, 24 };
	gen_report(steps);
}