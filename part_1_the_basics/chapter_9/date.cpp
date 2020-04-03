#include "date.h"
#include <stdexcept>
#include <sstream>

Date::Date(int y, Month m, int d) : y{ y }, m{ m }, d{ d } {
	if (!is_valid(*this))
	{
		std::stringstream ss;
		ss << *this;
		error(ss.str() + " is not a valid date");
	}
}

// --------------------------------------------------
// helper functions
// --------------------------------------------------

bool is_valid(const Date& d)
{
	bool is_valid = d.year() > 0 && (int(d.month()) > 0 
								&& int(d.month()) < 13) 
								&& d.day() > 0;
	is_valid = is_valid && (
		(is_31_day_month(d.month()) && d.day() < 32) ||
		(is_30_day_month(d.month()) && d.day() < 31) ||
		(d.month() == Month::feb && (is_leap(d.year()) && d.day() < 30) || d.day() < 29)
		);
	return is_valid;
}

bool is_leap(int year)
{
	return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

bool is_30_day_month(Month m)
{
	return m == Month::apr || m == Month::jun || m == Month::sep || m == Month::nov;
}

bool is_31_day_month(Month m)
{
	return m != Month::feb && !is_30_day_month(m);
}

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
	return os << '(' << d.year()
		<< ',' << int(d.month())
		<< ',' << d.day() << ')';
}