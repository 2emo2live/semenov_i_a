#include <bitseti/bitseti.h>
#include <bitset/bitset.h>
#include <cstdint>
#include <vector>

//По поводу хранения битов: минимальное значение (int a = 1) соответствует старшему биту в битсете (b[n-1])

Bitset::Bitset(const int64_t size, const bool v)
	: b_size(size)
	, cap((b_size + sizeof(T) * 8 - 1) / (sizeof(T) * 8))
{
	if (b_size < 0)
		throw std::invalid_argument("Bitset error: Bitset size can not be negative");
	T a = 0;
	std::vector<T> b(cap, (~a) * v);
	bits = b;
}

Bitset& Bitset::operator=(const Bitset& rhs) {
	b_size = rhs.b_size;
	cap = rhs.cap;
	bits = rhs.bits;
	return *this;
}

Bitset& Bitset::operator&=(const Bitset& rhs) {
	if (b_size != rhs.b_size)
		throw std::logic_error("Bitset error: b_sizes of operands do not match");
	else {
		for (int i = 0; i < cap; i++)
			bits[i] &= rhs.bits[i];
	}
	return *this;
}

Bitset& Bitset::operator|=(const Bitset& rhs) {
	if (b_size != rhs.b_size)
		throw std::logic_error("Bitset error: b_sizes of operands do not match");
	else {
		for (int i = 0; i < cap; i++)
			bits[i] |= rhs.bits[i];
	}
	return *this;
}

Bitset& Bitset::operator^=(const Bitset& rhs) {
	if (b_size != rhs.b_size)
		throw std::logic_error("Bitset error: b_sizes of operands do not match");
	else {
		for (int i = 0; i < cap; i++)
			bits[i] ^= rhs.bits[i];
	}
	return *this;
}

Bitset& Bitset::operator<<=(const int64_t rhs) {
	if (rhs < 0)
		throw std::invalid_argument("Bitset error: bitwise shift by negative count is undefined");
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

Bitset& Bitset::operator>>=(const int64_t rhs) {
	if (rhs < 0)
		throw std::invalid_argument("Bitset error: bitwise shift by negative count is undefined");
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

bool Bitset::operator==(const Bitset& rhs) const {
	if (b_size != rhs.size())
		return false;
	if (b_size == 0)
		return true;
	for (int i = 0; i < cap - 1; i++)
		if (bits[i] != rhs.bits[i])
			return false;
	T mask = ~0;
	mask <<= (b_size % (sizeof(T) * 8));
	if ((b_size % (sizeof(T)*8)) != 0)
		mask = ~mask;
	if ((bits[cap - 1] & mask) != (rhs.bits[rhs.cap - 1] & mask))
		return false;
	return true;
}

bool Bitset::operator!=(const Bitset& rhs) const {
	return !operator==(rhs);
}

Bitset Bitset::operator~() const {
	Bitset a = *this;
	for (int i = 0; i < cap; i++)
		a.bits[i] = ~bits[i];
	return a;
}

int64_t Bitset::size() const {
	return b_size;
}

Bitset operator&(const Bitset& lhs, const Bitset& rhs) {
	Bitset a;
	a = lhs;
	a &= rhs;
	return a;
}

Bitset operator|(const Bitset& lhs, const Bitset& rhs) {
	Bitset a;
	a = lhs;
	a |= rhs;
	return a;
}

Bitset operator^(const Bitset& lhs, const Bitset& rhs)
{
	Bitset a;
	a = lhs;
	a ^= rhs;
	return a;
}

Bitset operator<<(const Bitset& lhs, const int64_t rhs) {
	Bitset a;
	a = lhs;
	a <<= rhs;
	return a;
}

Bitset operator>>(const Bitset& lhs, const int64_t rhs) {
	Bitset a;
	a = lhs;
	a >>= rhs;
	return a;
}

std::ostream& operator<<(std::ostream& ostream, const Bitset& data) {
	return data.writeTo(ostream);
}

std::istream& operator>>(std::istream& istream, Bitset& data) {
	return data.readFrom(istream);
}

void Bitset::resize(const int64_t size, const bool filler) {
	if (size < 0)
		throw std::invalid_argument("Bitset error: Bitset size can not be negative");
	else if (size < b_size) {
		*this <<= (b_size - size);
		b_size = size;
		cap = (b_size + sizeof(T) * 8 - 1) / (sizeof(T) * 8);
	}
	else if (size > b_size) {
		for (int i = 0; i < (size - b_size + sizeof(T)*8 - 1) / (sizeof(T) * 8); i++)
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

std::ostream& Bitset::writeTo(std::ostream& ostream) const {
	T mask = 1;
	for (int i = 0; i < cap - 1; i++) {
		mask = 1;
		for (int j = 0; j < (sizeof(T) * 8); j++) {
			ostream << ((bits[i] & mask) == mask);
			mask <<= 1;
		}
//		std::cout << ' ';
	}
	mask = 1;
	for (int j = 0; j < b_size % (sizeof(T)*8); j++) {
		ostream << ((bits[cap - 1] & mask) == mask);
		mask <<= 1;
	}
	return ostream;
}

std::istream& Bitset::readFrom(std::istream& istream)
{
	std::string s;
//	istream >> s;
	char c, d;
	istream >> c;
	if ((c == '0') || (c == '1'))
		s += c;
	c = istream.peek();
	while (((c == '0') || (c == '1')) && (istream.eof() != true)) {
		istream >> d;
		s += d;
		c = istream.peek();
	}
	if (((istream.good()) || (istream.eof())) && (istream.bad() == false) && (s.length() > 0)) {
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
			*this = Bitset(j - i + 1);
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
	else {
		istream.setstate(std::ios_base::failbit);
	}
}

Bitset::BitHolder::BitHolder(T& b, const int p)
	: byte(b)
	, pos(p)
{
}

Bitset::BitHolder& Bitset::BitHolder::operator=(const bool rhs)
{
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

Bitset::BitHolder::operator bool() const
{
	T mask = 1;
	mask <<= pos;
	return ((byte & mask) != 0);
}

Bitset::BitHolder Bitset::operator[](const int64_t position)
{
	if ((position < 0) || (position >= b_size))
		throw std::out_of_range("Bitset error: index out of range");
	if (position == b_size - 1)
		return BitHolder(bits[0], 0);
	return BitHolder(bits[((b_size - 1 - position) + sizeof(T)*8) / (sizeof(T) * 8) - 1], (b_size - 1 - position) % (sizeof(T)*8));
}

bool Bitset::operator[](const int64_t position) const
{
	if ((position < 0) || (position >= b_size))
		throw std::out_of_range("Bitset error: index out of range");
	T mask = 1;
	mask <<= position;
	if (position == b_size - 1)
		return ((bits[0] & mask) != 0);
	return ((bits[((b_size - 1 - position) + sizeof(T) * 8) / (sizeof(T) * 8) - 1] & mask) != 0);
}

std::ostream& Bitset::WriteTo(std::ostream& ostream) const {
	std::cout << '0';
	Bitset::writeTo(ostream);
	return ostream;
};
std::istream& Bitset::ReadFrom(std::istream& istream) {
	Bitset::readFrom(istream);
	return istream;
};