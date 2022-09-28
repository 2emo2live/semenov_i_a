#ifndef BITSET
#define BITSET

#include <cstdint>
#include <vector>
#include <iostream>
#include <bitseti/bitseti.h>

class Bitset: public virtual BitsetI {
public:
	Bitset() = default;

	class BitHolder {
	public:
		friend class Bitset;
		BitHolder& operator=(const bool rhs);
		~BitHolder() = default;
		operator bool() const;
	private:
		BitHolder(T& b, const int p);
		T& byte;
		int pos;
	};
	Bitset(const Bitset& copy) = default;

	Bitset(const int64_t b_size, const bool v = false);

	Bitset& operator=(const Bitset& rhs);
	Bitset& operator&=(const Bitset& rhs);
	Bitset& operator|=(const Bitset& rhs);
	Bitset& operator^=(const Bitset& rhs);
	Bitset& operator<<=(const int64_t rhs);
	Bitset& operator>>=(const int64_t rhs);

	~Bitset() = default;

	bool operator==(const Bitset& rhs) const;
	bool operator!=(const Bitset& rhs) const;

	Bitset operator~() const;

	bool operator[] (const int64_t position) const;
	BitHolder operator[] (const int64_t position);

	int64_t size() const;
	void resize(const int64_t size, const bool filler = false);
	std::ostream& writeTo(std::ostream& ostream) const;
	std::istream& readFrom(std::istream& istream);
	std::ostream& WriteTo(std::ostream& ostream) const override;
	std::istream& ReadFrom(std::istream& istream) override;


private:
	int64_t b_size = 0;
	std::vector<T> bits;
	int64_t cap = 0;
};

Bitset operator&(const Bitset& lhs, const Bitset& rhs);
Bitset operator|(const Bitset& lhs, const Bitset& rhs);
Bitset operator^(const Bitset& lhs, const Bitset& rhs);
Bitset operator<<(const Bitset& lhs, const int64_t rhs);
Bitset operator>>(const Bitset& lhs, const int64_t rhs);

std::ostream& operator<<(std::ostream& ostream, const Bitset& data);
std::istream& operator>>(std::istream& istream, Bitset& data);


#endif