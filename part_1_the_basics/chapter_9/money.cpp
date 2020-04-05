// Rev 1. Complement exercise 14 of chapter 9
// Rev 2. Complement exercise 15 of chapter 9
// Rev 3. Complement exercise 16 of chapter 9

#include "money.h"

#include <stdexcept>

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

Money::Money(double money, const std::string& currency) : cents{ 0 }, currency{currency}
{
	if (!is_money_valid(money))
	{
		error("Error in Money::Money() - '" 
			+ std::to_string(money) + "' is not valid.");
	}
	if (currency.empty() || currency.size() != 3)
	{
		error("Error in Money::Money() - Currency code must be provided according to ISO 4217.");
	}
	cents = static_cast<long>(money * 100);
}

bool is_money_valid(double money)
{
	return money * 100 <= LONG_MAX;
}

std::ostream& operator<<(std::ostream& os, const Money& m)
{
	long c = m.get_cents();
	os << (c < 0 ? "-" : "")
		<< m.get_currency()
		<< (c < 0 ? c / (-100.0) : c / 100.0);
	return os;
}

Money operator+(const Money& lhs, const Money& rhs)
{
	if (lhs.get_currency() != rhs.get_currency())
	{
		error("Error in operator+() - Summation of '"
			+ lhs.get_currency() + "' and '"
			+ rhs.get_currency() + "' is not defined.");
	}
	return Money{ (lhs.get_cents() + double(rhs.get_cents())) / 100.0, lhs.get_currency() };
}

Money operator-(const Money& lhs, const Money& rhs)
{
	if (lhs.get_currency() != rhs.get_currency())
	{
		error("Error in operator-() - Subtraction of '" 
			+ lhs.get_currency() + "' and '"
			+ rhs.get_currency() + "' is not defined.");
	}
	return Money{ (lhs.get_cents() - double(rhs.get_cents())) / 100.0, lhs.get_currency() };
}

Money operator*(const Money& lhs, double rhs)
{
	return Money{ lhs.get_cents() / 100.0 * rhs, lhs.get_currency() };
}

Money operator/(const Money& lhs, double rhs)
{
	if (rhs == 0)
	{
		error("Error in operator*() - Division by zero is prohibited.");
	}
	return Money{ lhs.get_cents() / 100.0 / rhs, lhs.get_currency() };
}

std::istream& operator>>(std::istream& is, Money& m)
{
	char c1;
	char c2;
	char c3;
	double d{ 0 };
	is >> c1 >> c2 >> c3 >> d;
	if (!is)
	{
		is.clear();
		std::string line;
		std::getline(is, line);
		error("Error in operator>>() - '" 
			+ std::string{c1,c2,c3} 
			+ line 
			+ "' is not a valid input. Example of valid input: 'USD345.24'.");
	}
	if (!(std::isalpha(c1) && std::isalpha(c2) && std::isalpha(c3)))
	{
		error("Error in operator>>() - '" 
			+ std::string{ c1, c2, c3 } 
			+ "' is not a currency code. Valid currency code must comply with ISO 4217.");
	}
	
	m = Money{ d,{c1,c2,c3} };
	return is;
}