// This file contains definitions for Rational class

#include "rational.h"

Rational::Rational(int numerator, int denominator) : numerator{numerator},
	denominator{denominator} { }

Rational& Rational::operator=(const Rational& rhs)
{
	if (this != &rhs)
		*this = rhs;
	return *this;
}

void Rational::set_denominator(int denominator)
{
	this->denominator = denominator;
}

double Rational::to_double() const
{
	return double(numerator) / denominator;
}

void Rational::set_numerator(int numerator)
{
	this->numerator = numerator;
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
	int numerator{ 0 };
	int denominator{ 0 };
	if (lhs.get_denominator() == rhs.get_denominator())
	{
		numerator = lhs.get_numerator() + rhs.get_numerator();
		denominator = lhs.get_denominator();
	}
	else
	{
		numerator = lhs.get_numerator() * rhs.get_denominator() +
			rhs.get_numerator() * lhs.get_denominator();
		denominator = lhs.get_denominator() * rhs.get_denominator();
	}
	return Rational{ numerator, denominator };
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
	int numerator{ 0 };
	int denominator{ 0 };
	if (lhs.get_denominator() == rhs.get_denominator())
	{
		numerator = lhs.get_numerator() - rhs.get_numerator();
		denominator = lhs.get_denominator();
	}
	else
	{
		numerator = lhs.get_numerator() * rhs.get_denominator() -
			rhs.get_numerator() * lhs.get_denominator();
		denominator = lhs.get_denominator() * rhs.get_denominator();
	}
	return Rational{ numerator, denominator };
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
	int numerator{ 0 };
	int denominator{ 0 };
	numerator = lhs.get_numerator() * rhs.get_numerator();
	denominator = lhs.get_denominator() * rhs.get_denominator();
	return Rational{ numerator, denominator };
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
	int numerator{ 0 };
	int denominator{ 0 };
	numerator = lhs.get_numerator() * rhs.get_denominator();
	denominator = lhs.get_denominator() * rhs.get_numerator();
	return Rational{ numerator, denominator };
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
	return lhs.get_denominator() == rhs.get_denominator()
		&& lhs.get_numerator() == rhs.get_numerator();
}

bool operator!=(const Rational& lhs, const Rational& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
	if (lhs.get_denominator() == rhs.get_denominator())
	{
		return lhs.get_numerator() < rhs.get_numerator();
	}
	else
	{
		auto lhs_num = lhs.get_numerator() * rhs.get_denominator();
		auto rhs_num = rhs.get_numerator() * lhs.get_denominator();
		return lhs_num < rhs_num;
	}
}

bool operator>(const Rational& lhs, const Rational& rhs)
{
	return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& r)
{
	os << r.get_numerator() << '/' << r.get_denominator();
	return os;
}