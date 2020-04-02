// This file contains solution for drill 4 of chapter 9

#include <iostream>
#include <stdexcept>
#include <sstream>

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
public:
	Date(int y, Month m, int d); // check for valid date and initialize
	Month month() const { return m; }
	int day() const { return d; }
	int year() const { return y; }

	void add_day(int n); // increase the Date by n days
	void add_month(int n); // increase the Date by n months
	void add_year(int n); // increase the Date by n years
private:
	int y; // year
	Month m;
	int d; // day
	bool is_valid();
	void increment_day();
};

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

Date::Date(int y, Month m, int d) : y{ y }, m{ m }, d{ d } {
	if (!is_valid())
	{
		std::stringstream ss;
		ss << *this;
		error(ss.str() + " is not a valid date");
	}
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

void Date::add_year(int n)
{
	if (n <= 0)
		error("add_year() - negative argument passed");
	if (m == Month::feb && d == 29 && !is_leap(y + n))
	{
		m = Month::mar;
		d = 1;
	}
	y += n;
}

void Date::add_month(int n)
{
	if (n <= 0)
		error("add_month() - negative argument passed");
	auto cur_month = m;
	auto next_month = int(m) + n;
	m = next_month <= 12 ? Month(next_month) : Month(next_month - 12);

	if ((m == Month::feb && ((d > 29 && is_leap(y)) || d > 28)) || (is_30_day_month(m) && d > 30))
	{
		d = 1;
		m = Month(int(m) + 1);
	}
	
	if (int(cur_month) <= int(m) || cur_month == Month::dec && int(m) >= 1)
		++y;
}

bool Date::is_valid()
{
	bool is_valid = y > 0 && (int(m) > 0 && int(m) < 13) && d > 0;
	is_valid = is_valid && (
		(is_31_day_month(m) && d < 32) ||
		(is_30_day_month(m) && d < 31) ||
		(m == Month::feb && (is_leap(y) && d < 30) || d < 29)
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
		if (is_leap(y))
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
	Date today{ 1996, Month::dec, 5 };
	Date tomorrow = today;

	try
	{
		tomorrow.add_year(23);
		tomorrow.add_month(5);
		std::cout << today
			<< '\n' << tomorrow << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}