#pragma once
#ifndef RATIONAL_RATIONAL_H_20220309
#define RATIONAL_RATIONAL_H_20220309

#include <iostream>

class Rational {
public:
	Rational() = default;
	explicit Rational(const double num);
	explicit Rational(const int num);
	Rational(const int numerator, const int denominator);

	bool operator==(const Rational& right) const { return(num == right.num) && (den == right.den); };
	bool operator==(const int right) const { return(num == right) && (den == 1); };
	bool operator!=(const Rational& right) const { return !operator==(right); };
	bool operator!=(const int right) const { return !operator==(right); };
	bool operator>(const Rational& right) const { return (num * right.den > right.num * den); };
	bool operator<(const Rational& right) const { return (num * right.den < right.num * den); };
	bool operator>(const int right) const { return (num > right * den); };
	bool operator<(const int right) const { return (num < right * den); };
	bool operator>=(const Rational& right) const { return (num * right.den >= right.num * den); };
	bool operator<=(const Rational& right) const { return (num * right.den <= right.num* den); };
	bool operator>=(const int right) const { return (num >= right * den); };
	bool operator<=(const int right) const { return (num <= right* den); };
	Rational& operator-();
	Rational& operator+();
	Rational& operator+=(const Rational& right);
	Rational& operator+=(const int right) { return operator+=(Rational(right)); };
	Rational& operator-=(const Rational& right);
	Rational& operator-=(const int right) { return operator-=(Rational(right)); };
	Rational& operator*=(const Rational& right);
	Rational& operator*=(const int right) { return operator+=(Rational(right)); };
	Rational& operator/=(const Rational& right);
	Rational& operator/=(const int right) { return operator+=(Rational(right)); };

	std::ostream& writeTo(std::ostream& ostrm) const;
	std::istream& readFrom(std::istream& istrm);

	~Rational() = default;

private:
	int num = 0;
	int den = 1;
	static const char div = '/';
	Rational& NOD(Rational& right);
};

Rational operator+(const Rational& left, const Rational& right);
Rational operator+(const Rational& left, const int right);
Rational operator+(const int left, const Rational& right);
Rational operator-(const Rational& left, const Rational& right);
Rational operator-(const Rational& left, const int right);
Rational operator-(const int left, const Rational& right);
Rational operator*(const Rational& left, const Rational& right);
Rational operator*(const Rational& left, const int right);
Rational operator*(const int left, const Rational& right);
Rational operator/(const Rational& left, const Rational& right);
Rational operator/(const Rational& left, const int right);
Rational operator/(const int left, const Rational& right);

bool operator>(const int left, const Rational right);
bool operator>=(const int left, const Rational right);
bool operator<(const int left, const Rational right);
bool operator<=(const int left, const Rational right);

/*bool operator>(const Rational left, const Rational& right) { return (left.num * right.den > right.num * left.den); };
bool operator<(const Rational left, const Rational& right) { return (left.num * right.den < right.num * left.den); };
bool operator>(const Rational left, const int right) { return (left.num > right * left.den); };
bool operator<(const Rational left, const int right) { return (left.num < right* left.den); };
bool operator>=(const Rational left, const Rational& right) { return (left.num * right.den >= right.num * left.den); };
bool operator<=(const Rational left, const Rational& right) { return (left.num * right.den <= right.num * left.den); };
bool operator>=(const Rational left, const int right) { return (left.num >= right * left.den); };
bool operator<=(const Rational left, const int right) { return (left.num <= right * left.den); };
bool operator<=(const int left, const Rational right) { return (right >= left); };
bool operator>=(const int left, const Rational right) { return (right <= left); };
bool operator<(const int left, const Rational right) { return (right > left); };
bool operator>(const int left, const Rational right) { return (right < left); };*/

std::ostream& operator<<(std::ostream& ostrm, const Rational& right);
std::istream& operator>>(std::istream& istrm, Rational& right);

#endif