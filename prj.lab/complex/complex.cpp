#include <complex/complex.h>
#include <iostream>
#include <sstream>

Complex::Complex(const double real, const double imaginary)
	: re(real)
	, im(imaginary)
{
}

Complex::Complex(const double real)
	: re(real)
	, im(0.0)
{
}

Complex Complex::operator+() {
	return *this;
};

Complex Complex::operator-() {
	re *= -1;
	im *= -1;
	return *this;
};

Complex& Complex::operator+=(const Complex& right) {
	re += right.re;
	im += right.im;
	return *this;
}

Complex& Complex::operator-=(const Complex& right) {
	re -= right.re;
	im -= right.im;
	return *this;
}

Complex& Complex::operator*=(const Complex& right) {
	double old_re = re;
	re = re * right.re - im * right.im;
	im = im * right.re + old_re * right.im;
	return *this;
}

Complex& Complex::operator/=(const Complex& right) {
	double old_re = re;
	re = (re * right.re + im * right.im)/(right.re*right.re + right.im*right.im);
	im = (im * right.re - old_re * right.im)/(right.re * right.re + right.im * right.im);
	return *this;
}

Complex operator+(const Complex& left, const Complex& right) {
	Complex sum = left;
	sum += right;
	return sum;
}

Complex operator+(const Complex& left, const double right) {
	return operator+(left, Complex(right));
}

Complex operator+(const double left, const Complex& right) {
	return operator+(Complex(left), right);
}

Complex operator-(const Complex& left, const Complex& right) {
	Complex sub = left;
	sub -= right;
	return sub;
}

Complex operator-(const Complex& left, const double right) {
	return operator-(left, Complex(right));
}

Complex operator-(const double left, const Complex& right) {
	return operator-(Complex(left), right);
}

Complex operator*(const Complex& left, const Complex& right) {
	Complex mul = left;
	mul *= right;
	return mul;
}

Complex operator*(const Complex& left, const double right) {
	return operator*(left, Complex(right));
}

Complex operator*(const double left, const Complex& right) {
	return operator*(Complex(left), right);
}

Complex operator/(const Complex& left, const Complex& right) {
	Complex div = left;
	div /= right;
	return div;
}

Complex operator/(const Complex& left, const double right) {
	return operator/(left, Complex(right));
}

Complex operator/(const double left, const Complex& right) {
	return operator/(Complex(left), right);
}

std::ostream& operator<<(std::ostream& ostrm, const Complex& right) {
	return right.writeTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, Complex& right) {
	return right.readFrom(istrm);
}

std::ostream& Complex::writeTo(std::ostream& ostrm) const {
	ostrm << leftBr << re << separator << im << rightBr;
	return ostrm;
}

std::istream& Complex::readFrom(std::istream& istrm) {
	char leftBr = 0;
	double real = 0.0;
	char comma = 0;
	double imaginary = 0.0;
	char rightBr = 0;
	istrm >> leftBr >> real >> comma >> imaginary >> rightBr;
	if (istrm.good()) {
		if ((Complex::leftBr == leftBr) && (Complex::separator == comma) && (Complex::rightBr == rightBr)) {
			re = real;
			im = imaginary;
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}

/*bool testParse(const std::string& str) {
	std::istringstream istrm(str);
	Complex z;
	istrm >> z;
	if (istrm.good()) {
		std::cout << "Read success: " << str << " -> " << z << std::endl;
	}
	else {
		std::cout << "Read error: " << str << " -> " << z << std::endl;
	}
	return istrm.good();
}*/