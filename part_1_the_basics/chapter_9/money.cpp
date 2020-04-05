// Rev 1. Complement exercise 14 of chapter 9

#include "money.h"

#include <stdexcept>
#include <regex>

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

Money::Money(long cents) : cents{ cents } { }

Money::Money(const std::string& money) : cents{ 0 }
{
	if (!is_money_valid(money))
		error("Error in Money::Money() - '" + money + "' is not valid.");
	cents = str_to_cents(money);
}

bool is_money_valid(const std::string& money)
{
	std::regex rgx{ "((\\$\\d+\.\\d\\d)|(\\$\\d+))|((-\\$\\d+\\.\\d\\d)|(-\\$\\d+))" };
	return std::regex_match(money, rgx);
}

long str_to_cents(const std::string& money)
{
	long cents{ 0 };
	bool is_negative = money.find('-') != std::string::npos;
	bool is_real = money.find('.') != std::string::npos;
	auto pos1 = money.find('$') + 1;
	
	if (is_real)
	{
		auto pos2 = money.find('.');
		cents += std::stol(money.substr(pos1, pos2 - pos1)) * 100;
		cents += std::stol(money.substr(pos2 + 1, money.size() - (pos2 + 1)));
	}
	else
		cents += std::stol(money.substr(pos1, money.size() - pos1)) * 100;

	if (is_negative)
		cents = cents * (-1);
	return cents;
}

std::ostream& operator<<(std::ostream& os, const Money& m)
{
	long c = m.get_cents();
	os << (c < 0 ? "-$" : "$")
		<< (c < 0 ? c / (-100.0) : c / 100.0);
	return os;
}

Money operator+(const Money& lhs, const Money& rhs)
{
	return Money{ lhs.get_cents() + rhs.get_cents() };
}

Money operator-(const Money& lhs, const Money& rhs)
{
	return Money{ lhs.get_cents() - rhs.get_cents() };
}

Money operator*(const Money& lhs, double rhs)
{
	return Money{ static_cast<long>((lhs.get_cents() / 100.0 * rhs) * 100) };
}

Money operator/(const Money& lhs, double rhs)
{
	return Money{ static_cast<long>((lhs.get_cents() / 100.0 / rhs) * 100) };
}