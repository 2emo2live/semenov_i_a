#include <bitseti/bitseti.h>
#include <bitset/bitset.h>
#include <bitsett/bitsett.h>
#include <bitsetd/bitsetd.h>
#include <string>
#include <cstdint>
#include <vector>


BitsetI* readBitsetFrom(std::istream& istream) {
	char s;
	istream >> s;
	if (((istream.good()) || (istream.eof())) && (istream.bad() == false)) {
		if (s == '0') {
			BitsetI* a = new Bitset();
			a->ReadFrom(istream);
			return a;
		}
		if (s == '1') {
			BitsetI* a = new BitsetT <uint64_t>();
			a->ReadFrom(istream);
			return a;
		}
		if (s == '2') {
			BitsetI* a = new BitsetT <uint32_t>();
			a->ReadFrom(istream);
			return a;
		}
		if (s == '3') {
			BitsetI* a = new BitsetT <uint16_t>();
			a->ReadFrom(istream);
			return a;
		}
		if (s == '4') {
			BitsetI* a = new BitsetT <uint8_t>();
			a->ReadFrom(istream);
			return a;
		}
		if (s == '5') {
			BitsetI* a = new BitsetD();
			a->ReadFrom(istream);
			return a;
		}
	}
}

BitsetP::BitsetP(BitsetI* b)
	: ptr(b)
{
}

BitsetP::~BitsetP() {
	delete ptr;
	ptr = nullptr;
}

BitsetP BitsetP::operator=(BitsetI* b)
{
	ptr = b;
	return *this;
}

BitsetI* BitsetP::operator->()
{
	return ptr;
}

BitsetI* BitsetP::operator*()
{
	return ptr;
}

