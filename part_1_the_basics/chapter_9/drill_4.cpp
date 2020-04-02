// This file contains solution for drill 4 of chapter 9

#include <iostream>
#include <stdexcept>
#include <sstream>

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
	int y; // year
	Month m;
	int d; // day
	void increment_day();
public:
	Date(int y, Month m, int d); // check for valid date and initialize
	void add_day(int n); // increase the Date by n days
	Month month() { return m; }
	int day() { return d; }
	int year() { return y; }
};

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

std::ostream& operator<<(std::ostream& os, Date& d)
{
	return os << '(' << d.year()
		<< ',' << int(d.month())
		<< ',' << d.day() << ')';
}

bool is_valid(Date& d);

Date::Date(int y, Month m, int d) : y{ y }, m{ m }, d{ d } 
{
	if (!is_valid(*this))
	{
		std::stringstream ss;
		ss << *this;
		error(ss.str() + " is not a valid date");
	}
}

bool is_leap(Date& d)
{
	return (d.year() % 4 == 0) && ((d.year() % 100 != 0) || (d.year() % 400 == 0));
}

bool is_30_day_month(Month m)
{
	return m == Month::apr || m == Month::jun || m == Month::sep || m == Month::nov;
}

bool is_31_day_month(Month m)
{
	return m != Month::feb && !is_30_day_month(m);
}

bool is_valid(Date& d)
{
	bool is_valid = d.year() > 0 && (int(d.month()) > 0 && int(d.month()) < 13) && d.day() > 0;
	is_valid = is_valid && (
		(is_31_day_month(d.month()) && d.day() < 32) ||
		(is_30_day_month(d.month()) && d.day() < 31) ||
		(d.month() == Month::feb && (is_leap(d) && d.day() < 30) || d.day() < 29)
		);
	return is_valid;
}

int next_val(int threshold, int val)
{
	return val != threshold ? val + 1 : 1;
}

void Date::increment_day()
{
	switch (m)
	{
	case Month::feb:
	{
		if (is_leap(*this))
			d = next_val(29, d);
		else
			d = next_val(28, d);
		break;
	}
	case Month::jan:
	case Month::mar:
	case Month::may:
	case Month::jul:
	case Month::aug:
	case Month::oct:
	case Month::dec:
		d = next_val(31, d);
		break;
	default:
		d = next_val(30, d);
	}

	// handles case when next day is the first day of next month
	if (d == 1)
	{
		m = Month(next_val(12, int(m)));
		if (m == Month::jan)
			++y;
	}
}

void Date::add_day(int n)
{
	if (n <= 0)
		error("add_day() - negative argument passed");
	for (int i = 0; i < n; ++i)
		increment_day();
}

int main()
{
	try
	{
		Date today{ 1978, Month::jun, 26 };
		Date tomorrow = today;
		tomorrow.add_day(10);
		std::cout << today
			<< '\n' << tomorrow << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}