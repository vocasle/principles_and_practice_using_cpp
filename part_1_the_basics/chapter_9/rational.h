// This file contains definition of Rational class

#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational
{
public:
	Rational(int numerator, int denominator);
	int get_numerator() const { return numerator; }
	int get_denominator() const { return denominator; }
	double to_double() const;
	void set_numerator(int numerator);
	void set_denominator(int denominator);
	Rational& operator =(const Rational& rhs);
private:
	int numerator;
	int denominator;
};

Rational operator +(const Rational& lhs, const Rational& rhs);
Rational operator -(const Rational& lhs, const Rational& rhs);
Rational operator *(const Rational& lhs, const Rational& rhs);
Rational operator /(const Rational& lhs, const Rational& rhs);
bool operator==(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
std::ostream& operator<<(std::ostream& os, const Rational& r);

#endif // !RATIONAL_H
