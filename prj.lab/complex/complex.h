#pragma once
#ifndef COMPLEX_COMPLEX_H_20220309
#define COMPLEX_COMPLEX_H_20220309

#include <iostream>
#include <sstream>
#include <cmath>

struct Complex {
	Complex() {}
	explicit Complex(const double real);
	Complex(const double real, const double imaginary);

	bool operator==(const Complex& right) const { return ((std::abs(re-right.re) < 2 * std::numeric_limits<double>::epsilon()) && (std::abs(im - right.im) < 2 * std::numeric_limits<double>::epsilon())); }
	bool operator!=(const Complex& right) const { return !operator==(right); }
	bool operator==(const double& right) const { return operator==(Complex(right)); };
	bool operator!=(const double& right) const { return !operator==(Complex(right)); };
	Complex operator+();
	Complex operator-();
	Complex& operator+=(const Complex& right);
	Complex& operator+=(const double right) { return operator+=(Complex(right)); }
	Complex& operator-=(const Complex& right);
	Complex& operator-=(const double right) { return operator-=(Complex(right)); }
	Complex& operator*=(const Complex& right);
	Complex& operator*=(const double right) { return operator*=(Complex(right)); }
	Complex& operator/=(const Complex& right);
	Complex& operator/=(const double right) { return operator/=(Complex(right)); }

	std::ostream& writeTo(std::ostream& ostrm) const;
	std::istream& readFrom(std::istream& istrm);

	double re = 0.0;
	double im = 0.0;

	static const char leftBr = '{';
	static const char separator = ',';
	static const char rightBr = '}';

};

Complex operator+(const Complex& left, const Complex& right);
Complex operator+(const Complex& left, const double right);
Complex operator+(const double left, const Complex& right);
Complex operator-(const Complex& left, const Complex& right);
Complex operator-(const Complex& left, const double right);
Complex operator-(const double left, const Complex& right);
Complex operator*(const Complex& left, const Complex& right);
Complex operator*(const Complex& left, const double right);
Complex operator*(const double left, const Complex& right);
Complex operator/(const Complex& left, const Complex& right);
Complex operator/(const Complex& left, const double right);
Complex operator/(const double left, const Complex& right);

std::ostream& operator<<(std::ostream& ostrm, const Complex& right);
std::istream& operator>>(std::istream& istrm, Complex& right);

bool testParse(const std::string& str);

#endif
