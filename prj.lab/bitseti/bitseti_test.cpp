#include <bitseti/bitseti.h>
#include <bitset/bitset.h>
#include <iostream>
#include <sstream>

int main() {
	for (int i = 1; i < 2; i++) {
		BitsetP p = readBitsetFrom(std::cin);
		p->WriteTo(std::cout);
	}
}