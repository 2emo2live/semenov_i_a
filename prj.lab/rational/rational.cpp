#include <rational/rational.h>
#include <iostream>
#include <sstream>
#include <string>

Rational::Rational(const int numerator, const int denominator)
	: num(numerator)
	, den(denominator)
{
	Rational::NOD(*this);
};

Rational::Rational(const int numerator)
	: num(numerator)
	, den(1)
{
};

Rational::Rational(const double numerator)
	: num((int)(numerator * 1000))
	, den(1000)
{
	Rational::NOD(*this);
};

Rational& Rational::NOD(Rational& right) {
	if (0 == right.den)
		throw std::invalid_argument("Zero denominator");
	int sign = 1;
	if (0 > right.num) {
		sign *= -1;
		right.num *= -1;
	};
	if (0 > right.den) {
		sign *= -1;
		right.den *= -1;
	}
	int a = right.num;
	int b = right.den;
	while ((0 < a) && (0 < b)) {
		if (a > b) {
			a += b;
			b = a - b;
			a -= b;
		}
		b -= b / a * a;
	};
	if (a > b)
		b = a;
	right.num /= b;
	right.num *= sign;
	right.den /= b;
	return right;
}

Rational& Rational::operator-() {
	num *= -1;
	return *this;
}

Rational& Rational::operator+() {
	return *this;
}

Rational& Rational::operator+=(const Rational& right) {
	num = num * right.den + right.num * den;
	den = den * right.den;
	Rational::NOD(*this);
	return *this;
}

Rational& Rational::operator-=(const Rational& right) {
	num = num * right.den - right.num * den;
	den = den * right.den;
	Rational::NOD(*this);
	return *this;
}

Rational& Rational::operator*=(const Rational& right) {
	num = num * right.num;
	den = den * right.den;
	Rational::NOD(*this);
	return *this;
}

Rational& Rational::operator/=(const Rational& right) {
	num = num * right.den;
	den = den * right.num;
	Rational::NOD(*this);
	return *this;
}

Rational operator+(const Rational& left, const Rational& right) {
	Rational sum = left;
	sum += right;
	return sum;
}

Rational operator+(const Rational& left, const int right) {
	return operator+(left, Rational(right));
}

Rational operator+(const int left, const Rational& right) {
	return operator+(Rational(left), right);
}

Rational operator-(const Rational& left, const Rational& right) {
	Rational sub = left;
	sub -= right;
	return sub;
}

Rational operator-(const Rational& left, const int right) {
	return operator-(left, Rational(right));
}

Rational operator-(const int left, const Rational& right) {
	return operator-(Rational(left), right);
}

Rational operator*(const Rational& left, const Rational& right) {
	Rational mul = left;
	mul *= right;
	return mul;
}

Rational operator*(const Rational& left, const int right) {
	return operator*(left, Rational(right));
}

Rational operator*(const int left, const Rational& right) {
	return operator*(Rational(left), right);
}

Rational operator/(const Rational& left, const Rational& right) {
	Rational div = left;
	div /= right;
	return div;
}

Rational operator/(const Rational& left, const int right) {
	return operator/(left, Rational(right));
}

Rational operator/(const int left, const Rational& right) {
	return operator/(Rational(left), right);
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& right) {
	return right.writeTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, Rational& right) {
	return right.readFrom(istrm);
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const {
	ostrm << num << div << den;
	return ostrm;
}

std::istream& Rational::readFrom(std::istream& istrm) {
	int numerator = 0;
	char div = 0;
	int denominator = 0;
//	istrm >> numerator >> div >> denominator;
	std::string s;
	istrm >> s;
//	std::cout << '-' << s << std::endl;
	if (((istrm.good()) || (istrm.eof())) && (istrm.bad() == false)) {
		try {
			int i = 0;
			while (s[i] == ' ') {
				i += 1;
			}
			int mn = 1;
			if (s[i] == '-') {
				mn *= -1;
				i += 1;
			}
//			std::cout << '-' << mn << std::endl;
			int j = i;
			while (s[j] != '/') {
				j += 1;
				if ((j > s.length() - 1) || (s[j] == '.')) {
					throw std::invalid_argument("");
				}
				if ((((int)s[j] < 48) || ((int)s[j] > 57)) && (s[j] != '/')) {
//					std::cout << s[j];
					throw std::invalid_argument("");
				}
			}
//			std::cout << "-" << i << ' ' << j << std::endl;
//			std::cout << "--" << std::stoi(s.substr(i, j - i)) << std::endl;
			numerator = mn*std::stoi(s.substr(i , j - i));
			div = s[j];
			i = j + 1;
			while ((s[i] != ' ') && (i <= s.length() - 1)) {
				i += 1;
				if ((((int)s[i] < 48) || ((int)s[i] > 57)) && ((int)s[i] > 32)) {
//					std::cout << s[i];
					throw std::invalid_argument("");
				}
			}
//			std::cout << "---" << j << " " << i << std::endl;
			denominator = std::stoi(s.substr(j + 1, i - j - 1));
//			std::cout << "----" << numerator << ' ' << denominator << std::endl;
			if ((Rational::div == div) && (denominator > 0)) {
				num = numerator;
				den = denominator;
				Rational::NOD(*this);
			}
			else {
				istrm.setstate(std::ios_base::failbit);
				throw std::invalid_argument("");
			}
		} catch (...) {
				istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}


bool operator>(const int left, const Rational right) {
	return (right.operator<(left));
}
bool operator<(const int left, const Rational right) {
	return (right.operator>(left));
}
bool operator>=(const int left, const Rational right) {
	return (right.operator<=(left));
}
bool operator<=(const int left, const Rational right) {
	return (right.operator>=(left));
}
