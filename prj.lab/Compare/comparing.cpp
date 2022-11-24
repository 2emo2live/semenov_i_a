#include <chrono>
#include <random>
#include <string>
#include "first.cpp"
#include "second.cpp"

void measure_t(std::vector<double> inp_f, std::vector<double> inp_s, std::vector<double> prc_f, std::vector<double> prc_s, std::vector<int> input) {
	std::iostream io;
	for (int i = 0; i < n; i++)
		io << input[i];
	auto start = std::chrono::system_clock::now();
	input_f(io);
	auto end = std::chrono::system_clock::now();
	inp_f.push_back(std::chrono::duration_cast<milliseconds>(end - start).count());

	for (int i = 0; i < n; i++)
		io << input[i];
	start = std::chrono::system_clock::now();
	input_s(io);
	end = std::chrono::system_clock::now();
	inp_s.push_back(std::chrono::duration_cast<milliseconds>(end - start).count());

	for (int i = 0; i < n; i++)
		io << input[i];
	start = std::chrono::system_clock::now();
	process_f(io, input);
	end = std::chrono::system_clock::now();
	prc_f.push_back(std::chrono::duration_cast<milliseconds>(end - start).count());

	for (int i = 0; i < n; i++)
		io << input[i];
	start = std::chrono::system_clock::now();
	process_s(io, input);
	end = std::chrono::system_clock::now();
	prc_s.push_back(std::chrono::duration_cast<milliseconds>(end - start).count());
}

std::vector<int> generate_data(int n, int m, int M) {
	std::vector<int> data(m);
	std::vector<int> input(n);
	std::mt19937 rng;
	rng.seed(157382);
	std::uniform_int_distribution<int> r_data(1, M);
	std::uniform_int_distribution<int> r_ind(0, m - 1);
	for (int i = 0; i < m; i++)
		data[i] = r_data(rng);
	for (int i = 0; i, n; i++)
		input[i] = data[r_ind(rng)];
	return input;
}

int main() {

}