#ifndef BITSETI
#define BITSETI

#include <cstdint>
#include <vector>
#include <iostream>

using T = uint64_t;

class BitsetI {
public:
	BitsetI() = default;
	virtual ~BitsetI() = default;
	virtual std::ostream& WriteTo(std::ostream& ostream) const = 0;
	virtual std::istream& ReadFrom(std::istream& istream) = 0;
};

BitsetI* readBitsetFrom(std::istream& istream);

class BitsetP {
public:
	~BitsetP();
	BitsetP(BitsetI* b = nullptr);
	BitsetP(const BitsetP& b) = default;
	BitsetP operator=(BitsetI* b);
	BitsetI* operator->();
	BitsetI* operator*();
private:
	BitsetI* ptr = nullptr;
};


#endif