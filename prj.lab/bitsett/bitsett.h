#ifndef BITSETT
#define BITSETT

#include <cstdint>
#include <vector>
#include <iostream>
#include <bitseti/bitseti.h>

template <typename T>
class BitsetT: public virtual BitsetI {
public:
	BitsetT() = default;

	class BitHolder {
	public:
		friend class BitsetT;
		BitHolder& operator=(const bool rhs) {
			T mask = 1;
			mask <<= pos;
			if (rhs) {
				byte |= mask;
			}
			else {
				mask = ~mask;
				byte &= mask;
			}
			return *this;
		}
		~BitHolder() = default;
		operator bool() const {
			T mask = 1;
			mask <<= pos;
			return ((byte & mask) != 0);
		}
	private:
		BitHolder(T& b, const int p)
			: byte(b)
			, pos(p)
		{
		}
		T& byte;
		int pos;
	};
	BitsetT(const BitsetT& copy) = default;

	BitsetT(const int64_t size, const bool v = false);

	BitsetT& operator=(const BitsetT& rhs);
	BitsetT& operator&=(const BitsetT& rhs);
	BitsetT& operator|=(const BitsetT& rhs);
	BitsetT& operator^=(const BitsetT& rhs);
	BitsetT& operator<<=(const int64_t rhs);
	BitsetT& operator>>=(const int64_t rhs);

	~BitsetT() = default;

	bool operator==(const BitsetT& rhs) const;
	bool operator!=(const BitsetT& rhs) const;

	BitsetT operator~() const;

	BitHolder operator[] (const int64_t position) {
		if ((position < 0) || (position >= b_size))
			throw std::out_of_range("Bitset error: index out of range");
		if (position == b_size - 1)
			return BitHolder(bits[0], 0);
		return BitHolder(bits[((b_size - 1 - position) + sizeof(T) * 8) / (sizeof(T) * 8) - 1], (b_size - 1 - position) % (sizeof(T) * 8));
	};
	bool operator[] (const int64_t position) const;

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

template <typename T>
BitsetT<T> operator&(const BitsetT<T>& lhs, const BitsetT<T>& rhs) {
	BitsetT<T> a;
	a = lhs;
	a &= rhs;
	return a;
}
template <typename T>
BitsetT<T> operator|(const BitsetT<T>& lhs, const BitsetT<T>& rhs) {
	BitsetT<T> a;
	a = lhs;
	a |= rhs;
	return a;
}
template <typename T>
BitsetT<T> operator^(const BitsetT<T>& lhs, const BitsetT<T>& rhs) {
	BitsetT<T> a;
	a = lhs;
	a ^= rhs;
	return a;
}
template <typename T>
BitsetT<T> operator<<(const BitsetT<T>& lhs, const BitsetT<T>& rhs) {
	BitsetT<T> a;
	a = lhs;
	a <<= rhs;
	return a;
}
template <typename T>
BitsetT<T> operator>>(const BitsetT<T>& lhs, const BitsetT<T>& rhs) {
	BitsetT<T> a;
	a = lhs;
	a >>= rhs;
	return a;
}

template <typename T>
std::ostream& operator<<(std::ostream& ostream, const BitsetT<T>& data) {
	return data.writeTo(ostream);
};
template <typename T>
std::istream& operator>>(std::istream& istream, BitsetT<T>& data) {
	return data.readFrom(istream);
};

template<typename T>
BitsetT<T>::BitsetT(const int64_t size, const bool v)
	: b_size(size)
	, cap((b_size + sizeof(T) * 8 - 1) / (sizeof(T) * 8))
{
	if (b_size < 0)
		throw std::invalid_argument("Bitset error: Bitset size can not be negative");
	T a = 0;
	std::vector<T> b(cap, (~a) * v);
	bits = b;
}

template<typename T>
BitsetT<T>& BitsetT<T>::operator=(const BitsetT& rhs) {
	b_size = rhs.b_size;
	cap = rhs.cap;
	bits = rhs.bits;
	return *this;
}

template<typename T>
BitsetT<T>& BitsetT<T>::operator&=(const BitsetT& rhs) {
	if (b_size != rhs.b_size)
		throw std::logic_error("BitsetT error: b_sizes of operands do not match");
	else {
		for (int i = 0; i < cap; i++)
			bits[i] &= rhs.bits[i];
	}
	return *this;
}

template<typename T>
BitsetT<T>& BitsetT<T>::operator|=(const BitsetT& rhs) {
	if (b_size != rhs.b_size)
		throw std::logic_error("BitsetT error: b_sizes of operands do not match");
	else {
		for (int i = 0; i < cap; i++)
			bits[i] |= rhs.bits[i];
	}
	return *this;
}

template<typename T>
BitsetT<T>& BitsetT<T>::operator^=(const BitsetT& rhs) {
	if (b_size != rhs.b_size)
		throw std::logic_error("BitsetT error: b_sizes of operands do not match");
	else {
		for (int i = 0; i < cap; i++)
			bits[i] ^= rhs.bits[i];
	}
	return *this;
}

template<typename T>
BitsetT<T>& BitsetT<T>::operator<<=(const int64_t rhs) {
	if (rhs < 0)
		throw std::logic_error("BitsetT error: b_sizes of operands do not match");
	else if (rhs == 0) {
		return *this;
	}
	else {
		T mask = 1;
		T help = 1;
		T help1 = 1;
		T clean = 1;
		clean <<= (b_size % (sizeof(T) * 8)) - 1;
		clean = ~clean;
		for (int j = 0; j < rhs; j++) {
			help = bits[cap - 1] & mask;
			bits[cap - 1] >>= 1;
			bits[cap - 1] &= clean;
			for (int i = cap - 2; i >= 0; i--) {
				help1 = bits[i] & mask;
				bits[i] >>= 1;
				help <<= sizeof(T) * 8 - 1;
				bits[i] |= help;
				help = help1;
			}
		}
	}
	return *this;
}

template<typename T>
BitsetT<T>& BitsetT<T>::operator>>=(const int64_t rhs) {
	if (rhs < 0)
		throw std::logic_error("BitsetT error: b_sizes of operands do not match");
	else if (rhs == 0) {
		return *this;
	}
	else {
		T mask = 1;
		mask <<= sizeof(T) * 8 - 1;
		T help = 1;
		T help1 = 1;
		for (int j = 0; j < rhs; j++) {
			help = bits[0] & mask;
			bits[0] <<= 1;
			for (int i = 1; i < cap; i++) {
				help1 = bits[i] & mask;
				bits[i] <<= 1;
				help >>= sizeof(T) * 8 - 1;
				bits[i] |= help;
				help = help1;
			}
		}
	}
	return *this;
}

template<typename T>
bool BitsetT<T>::operator==(const BitsetT& rhs) const {
	if (b_size != rhs.size())
		return false;
	if (b_size == 0)
		return true;
	for (int i = 0; i < cap - 1; i++)
		if (bits[i] != rhs.bits[i])
			return false;
	T mask = ~0;
	mask <<= (b_size % (sizeof(T) * 8));
	if ((b_size % (sizeof(T) * 8)) != 0)
		mask = ~mask;
	if ((bits[cap - 1] & mask) != (rhs.bits[rhs.cap - 1] & mask))
		return false;
	return true;
}

template<typename T>
bool BitsetT<T>::operator!=(const BitsetT& rhs) const {
	return !operator==(rhs);
}

template<typename T>
BitsetT<T> BitsetT<T>::operator~() const {
	Bitset<T> a = *this;
	for (int i = 0; i < cap; i++)
		a.bits[i] = ~bits[i];
	return a;
}

template<typename T>
bool BitsetT<T>::operator[](const int64_t position) const
{
	if ((position < 0) || (position >= b_size))
		throw std::out_of_range("BitsetT error: index out of range");
	T mask = 1;
	mask <<= position;
	if (position == b_size - 1)
		return ((bits[0] & mask) != 0);
	return ((bits[((b_size - 1 - position) + sizeof(T) * 8) / (sizeof(T) * 8) - 1] & mask) != 0);
}

template<typename T>
int64_t BitsetT<T>::size() const {
	return b_size;
}

template<typename T>
void BitsetT<T>::resize(const int64_t size, const bool filler) {
	if (size < 0)
		throw std::invalid_argument("Bitset error: Bitset size can not be negative");
	else if (size < b_size) {
		*this <<= (b_size - size);
		b_size = size;
		cap = (b_size + sizeof(T) * 8 - 1) / (sizeof(T) * 8);
	}
	else if (size > b_size) {
		for (int i = 0; i < (size - b_size + sizeof(T) * 8 - 1) / (sizeof(T) * 8); i++)
			bits.push_back(~0);
		int delt = size - b_size;
		b_size = size;
		cap = (b_size + sizeof(T) * 8 - 1) / (sizeof(T) * 8);
		if (filler) {
			for (int i = 1; i <= delt; i++) {
				*this >>= 1;
				bits[0] |= 1;
			}
		}
		else
			*this >>= delt;
	}
}

template<typename T>
std::ostream& BitsetT<T>::writeTo(std::ostream& ostream) const {
	T mask = 1;
	for (int i = 0; i < cap - 1; i++) {
		mask = 1;
		for (int j = 0; j < (sizeof(T) * 8); j++) {
			ostream << ((bits[i] & mask) == mask);
			mask <<= 1;
		}
	}
	mask = 1;
	for (int j = 0; j < b_size % (sizeof(T) * 8); j++) {
		ostream << ((bits[cap - 1] & mask) == mask);
		mask <<= 1;
	}
	return ostream;
}
template<typename T>
std::istream& BitsetT<T>::readFrom(std::istream& istream) {
	std::string s;
	istream >> s;
	if (((istream.good()) || (istream.eof())) && (istream.bad() == false)) {

		try {
			int i = 0;
			while (s[i] == ' ') {
				i += 1;
				if (i >= s.length())
					break;
			}
			int j = s.length() - 1;
			while ((s[j] != '0') && (s[j] != '1')) {
				j -= 1;
				if (j <= 0)
					break;
			}
			if (j - i + 1 <= 0)
				throw std::invalid_argument("");
			if ((j - i + 1 == 1) && (s[i] != '0') && (s[i] != '1'))
				throw std::invalid_argument("");
			*this = BitsetT<T>(j - i + 1);
			for (int k = i; k <= j; k++) {
				int mask = (s[k] == '1');
				mask <<= (b_size % (sizeof(T) * 8)) - 1;
				*this <<= 1;
				bits[cap - 1] |= mask;
			}
		}
		catch (...) {
			istream.setstate(std::ios_base::failbit);
		}
	}
}
template<typename T>
std::ostream& BitsetT<T>::WriteTo(std::ostream& ostream) const {
	if (typeid(T) == typeid(uint64_t))
		std::cout << '1';
	else if (typeid(T) == typeid(uint32_t))
		std::cout << '2';
	else if (typeid(T) == typeid(uint16_t))
		std::cout << '3';
	else if (typeid(T) == typeid(uint8_t))
		std::cout << '4';
	BitsetT::writeTo(ostream);
	return ostream;
}
template<typename T>
inline std::istream& BitsetT<T>::ReadFrom(std::istream& istream) {
	BitsetT::readFrom(istream);
	return istream;
};

#endif