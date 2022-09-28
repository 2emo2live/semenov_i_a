#include <bitseti/bitseti.h>
#include <bitsetd/bitsetd.h>
#include <cstdint>
#include <vector>

void BitsetD::arr_copy(uint64_t* data1, uint64_t* data2, int64_t size)
{
	for (int i = 0; i < size; i++)
		data1[i] = data2[i];
}

BitsetD::BitsetD(const BitsetD& copy)
{
	if (copy.data_ != data_) {
		if (b_size < copy.b_size) {
			b_size = copy.b_size;
			cap = copy.cap;
			delete[] data_;
			data_ = new T[cap];
		}
		b_size = copy.b_size;
		cap = copy.cap;
		arr_copy(data_, copy.data_, cap);
	}
}

BitsetD::BitsetD(const int64_t size, const bool v)
	: b_size(size)
	, cap((b_size + sizeof(T) * 8 - 1) / (sizeof(T) * 8))
{
	if (b_size < 0)
		throw std::invalid_argument("BitsetD error: BitsetD size can not be negative");
	T a = 0;
	data_ = new T[cap];
	for (int i = 0; i < cap; i++)
		data_[i] = (~a) * v;
}

BitsetD& BitsetD::operator=(const BitsetD& rhs) {
	if (b_size < rhs.b_size) {
		delete[] data_;
		data_ = new T[(rhs.b_size + sizeof(T) * 8 - 1) / (sizeof(T) * 8)];
		arr_copy(data_, rhs.data_, (rhs.cap));
	}
	b_size = rhs.b_size;
	cap = rhs.cap;
	arr_copy(data_, rhs.data_, (cap));
	return *this;
}

BitsetD& BitsetD::operator&=(const BitsetD& rhs) {
	if (b_size != rhs.b_size)
		throw std::logic_error("BitsetD error: b_sizes of operands do not match");
	else {
		for (int i = 0; i < (cap); i++) {
			data_[i] &= rhs.data_[i];
		}
	}
	return *this;
}

BitsetD& BitsetD::operator|=(const BitsetD& rhs) {
	if (b_size != rhs.b_size)
		throw std::logic_error("BitsetD error: b_sizes of operands do not match");
	else {
		for (int i = 0; i < (cap); i++) {
			data_[i] |= rhs.data_[i];
		}
	}
	return *this;
}

BitsetD& BitsetD::operator^=(const BitsetD& rhs) {
	if (b_size != rhs.b_size)
		throw std::logic_error("BitsetD error: b_sizes of operands do not match");
	else {
		for (int i = 0; i < (cap); i++) {
			data_[i] ^= rhs.data_[i];
		}
	}
	return *this;
}

BitsetD& BitsetD::operator<<=(const int64_t rhs) {
	if (rhs < 0)
		throw std::logic_error("BitsetD error: b_sizes of operands do not match");
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
			help = data_[cap - 1] & mask;
			data_[cap - 1] >>= 1;
			data_[cap - 1] &= clean;
			for (int i = cap - 2; i >= 0; i--) {
				help1 = data_[i] & mask;
				data_[i] >>= 1;
				help <<= sizeof(T) * 8 - 1;
				data_[i] |= help;
				help = help1;
			}
		}
	}
	return *this;
}

BitsetD& BitsetD::operator>>=(const int64_t rhs) {
	if (rhs < 0)
		throw std::logic_error("BitsetD error: b_sizes of operands do not match");
	else if (rhs == 0) {
		return *this;
	}
	else {
		T mask = 1;
		mask <<= sizeof(T) * 8 - 1;
		T help = 1;
		T help1 = 1;
		for (int j = 0; j < rhs; j++) {
			help = data_[0] & mask;
			data_[0] <<= 1;
			for (int i = 1; i < cap; i++) {
				help1 = data_[i] & mask;
				data_[i] <<= 1;
				help >>= sizeof(T) * 8 - 1;
				data_[i] |= help;
				help = help1;
			}
		}
	}
	return *this;
}

BitsetD::~BitsetD() {
	delete[] data_;
	data_ = nullptr;
}

bool BitsetD::operator==(const BitsetD& rhs) const {
	if (b_size != rhs.size())
		return false;
	if (b_size == 0)
		return true;
	for (int i = 0; i < cap - 1; i++)
		if (data_[i] != rhs.data_[i])
			return false;
	T mask = ~0;
	mask <<= (b_size % (sizeof(T) * 8));
	if ((b_size % (sizeof(T) * 8)) != 0)
		mask = ~mask;
	if ((data_[cap - 1] & mask) != (rhs.data_[rhs.cap - 1] & mask))
		return false;
	return true;
}

bool BitsetD::operator!=(const BitsetD& rhs) const {
	return !operator==(rhs);
}

BitsetD BitsetD::operator~() {
	for (int i = 0; i < cap; i++)
		data_[i] = ~data_[i];
	return *this;
}

int64_t BitsetD::size() const {
	return b_size;
}

BitsetD operator&(const BitsetD& lhs, const BitsetD& rhs) {
	BitsetD a;
	a = lhs;
	a &= rhs;
	return a;
}

BitsetD operator|(const BitsetD& lhs, const BitsetD& rhs) {
	BitsetD a;
	a = lhs;
	a |= rhs;
	return a;
}

BitsetD operator^(const BitsetD& lhs, const BitsetD& rhs)
{
	BitsetD a;
	a = lhs;
	a ^= rhs;
	return a;
}

BitsetD operator<<(const BitsetD& lhs, const int64_t rhs) {
	BitsetD a;
	a = lhs;
	a <<= rhs;
	return a;
}

BitsetD operator>>(const BitsetD& lhs, const int64_t rhs) {
	BitsetD a;
	a = lhs;
	a >>= rhs;
	return a;
}

std::ostream& operator<<(std::ostream& ostream, const BitsetD& data) {
	return data.writeTo(ostream);
}

std::istream& operator>>(std::istream& istream, BitsetD& data) {
	return data.readFrom(istream);
}

void BitsetD::resize(const int64_t size, const bool filler) {
	if (size < 0)
		throw std::invalid_argument("Bitset error: Bitset size can not be negative");
	else if (size < b_size) {
		*this <<= (b_size - size);
		b_size = size;
		cap = (b_size + sizeof(T) * 8 - 1) / (sizeof(T) * 8);
	}
	else if (size > b_size) {
		if (((size + sizeof(T) * 8 - 1) / (sizeof(T) * 8)) > cap) {
			T* b = new T[(size + sizeof(T) * 8 - 1) / (sizeof(T) * 8)];
			arr_copy(b, data_, cap);
			for (int i = cap - 1; i < (size + sizeof(T) * 8 - 1) / ((sizeof(T) * 8)) - 1; i++)
				b[i] = ~0;
			delete[] data_;
			data_ = new T[(size + sizeof(T) * 8 - 1) / (sizeof(T) * 8)];
			arr_copy(data_, b, (size + sizeof(T) * 8 - 1) / (sizeof(T) * 8));
			delete[] b;
			b = nullptr;
		}
		int delt = size - b_size;
		b_size = size;
		cap = (b_size + sizeof(T) * 8 - 1) / (sizeof(T) * 8);
		if (filler) {
			for (int i = 1; i <= delt; i++) {
				*this >>= 1;
				data_[0] |= 1;
			}
		}
		else
			*this >>= delt;
	}
}

std::ostream& BitsetD::writeTo(std::ostream& ostream) const {
	T mask = 1;
	for (int i = 0; i < cap - 1; i++) {
		mask = 1;
		for (int j = 0; j < (sizeof(T) * 8); j++) {
			ostream << ((data_[i] & mask) == mask);
			mask <<= 1;
		}
		//		std::cout << ' ';
	}
	mask = 1;
	for (int j = 0; j < b_size % (sizeof(T) * 8); j++) {
		ostream << ((data_[cap - 1] & mask) == mask);
		mask <<= 1;
	}
	return ostream;
}

std::istream& BitsetD::readFrom(std::istream& istream)
{
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
			*this = BitsetD(j - i + 1);
			for (int k = i; k <= j; k++) {
				int mask = (s[k] == '1');
				mask <<= (b_size % (sizeof(T) * 8)) - 1;
				*this <<= 1;
				data_[cap - 1] |= mask;
			}
		}
		catch (...) {
			istream.setstate(std::ios_base::failbit);
		}
	}
}

BitsetD::BitHolder::BitHolder(T& b, const int p)
	: byte(b)
	, pos(p)
{
}

BitsetD::BitHolder& BitsetD::BitHolder::operator=(const bool rhs)
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

BitsetD::BitHolder::operator bool() const
{
	T mask = 1;
	mask <<= pos;
	return ((byte & mask) != 0);
}

BitsetD::BitHolder BitsetD::operator[](const int64_t position)
{
	if ((position < 0) || (position >= b_size))
		throw std::out_of_range("Bitset error: index out of range");
	if (position == b_size - 1)
		return BitHolder(data_[0], 0);
	return BitHolder(data_[((b_size - 1 - position) + sizeof(T) * 8) / (sizeof(T) * 8) - 1], (b_size - 1 - position) % (sizeof(T) * 8));
}

bool BitsetD::operator[](const int64_t position) const
{
	if ((position < 0) || (position >= b_size))
		throw std::out_of_range("Bitset error: index out of range");
	T mask = 1;
	mask <<= position;
	if (position == b_size - 1)
		return ((data_[0] & mask) != 0);
	return ((data_[((b_size - 1 - position) + sizeof(T) * 8) / (sizeof(T) * 8) - 1] & mask) != 0);
}

std::ostream& BitsetD::WriteTo(std::ostream& ostream) const {
	std::cout << '5';
	BitsetD::writeTo(ostream);
	return ostream;
};
std::istream& BitsetD::ReadFrom(std::istream& istream) {
	BitsetD::readFrom(istream);
	return istream;
};