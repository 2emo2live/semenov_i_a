#ifndef BITSETD
#define BITSETD

#include <cstdint>
#include <vector>
#include <iostream>
#include <bitseti/bitseti.h>

class BitsetD : public virtual BitsetI {
public:
	BitsetD() = default;

	class BitHolder {
	public:
		friend class BitsetD;
		BitHolder& operator=(const bool rhs);
		~BitHolder() = default;
		operator bool() const;
	private:
		BitHolder(T& b, const int p);
		T& byte;
		int pos;
	};
	BitsetD(const BitsetD& copy);

	BitsetD(const int64_t b_size, const bool v = false);

	BitsetD& operator=(const BitsetD& rhs);
	BitsetD& operator&=(const BitsetD& rhs);
	BitsetD& operator|=(const BitsetD& rhs);
	BitsetD& operator^=(const BitsetD& rhs);
	BitsetD& operator<<=(const int64_t rhs);
	BitsetD& operator>>=(const int64_t rhs);

	~BitsetD();

	bool operator==(const BitsetD& rhs) const;
	bool operator!=(const BitsetD& rhs) const;

	BitsetD operator~();

	bool operator[] (const int64_t position) const;
	BitHolder operator[] (const int64_t position);

	int64_t size() const;
	void resize(const int64_t size, const bool filler = false);
	std::ostream& writeTo(std::ostream& ostream) const;
	std::istream& readFrom(std::istream& istream);
	std::ostream& WriteTo(std::ostream& ostream) const override;
	std::istream& ReadFrom(std::istream& istream) override;


private:
	void arr_copy(uint64_t* data1, uint64_t* data2, int64_t size);
	int64_t b_size = 0;
	uint64_t* data_{ nullptr };
	int64_t cap = 0;
};

BitsetD operator&(const BitsetD& lhs, const BitsetD& rhs);
BitsetD operator|(const BitsetD& lhs, const BitsetD& rhs);
BitsetD operator^(const BitsetD& lhs, const BitsetD& rhs);
BitsetD operator<<(const BitsetD& lhs, const int64_t rhs);
BitsetD operator>>(const BitsetD& lhs, const int64_t rhs);

std::ostream& operator<<(std::ostream& ostream, const BitsetD& data);
std::istream& operator>>(std::istream& istream, BitsetD& data);


#endif