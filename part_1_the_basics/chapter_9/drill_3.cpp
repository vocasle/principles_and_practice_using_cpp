// This file contains solution for drill 3 of chapter 9

#include <iostream>
#include <stdexcept>
#include <sstream>

class Date {
	int y, m, d; // year, month, day
	void increment_day();
public:
	Date(int y, int m, int d); // check for valid date and initialize
	void add_day(int n); // increase the Date by n days
	int month() { return m; }
	int day() { return d; }
	int year() { return y; }
};

std::ostream& operator<<(std::ostream& os, Date& d);
bool is_valid(Date& d);
void error(const std::string& msg);

Date::Date(int y, int m, int d) : y{ y }, m{ m }, d{ d } 
{
	if (!is_valid(*this))
	{
		std::stringstream ss;
		ss << *this;
		error(ss.str() + " is not a valid date");
	}
}

std::ostream& operator<<(std::ostream& os, Date& d)
{
	return os << '(' << d.year()
		<< ',' << d.month()
		<< ',' << d.day() << ')';
}

bool is_leap(Date& d)
{
	return (d.year() % 4 == 0) && ((d.year() % 100 != 0) || (d.year() % 400 == 0));
}

bool is_30_day_month(int m)
{
	return m == 4 || m == 6 || m == 9 || m == 11;
}

bool is_31_day_month(int m)
{
	return m != 2 && !is_30_day_month(m);
}

bool is_valid(Date& d)
{
	bool is_valid = d.year() > 0 && (d.month() > 0 && d.month() < 13) && d.day() > 0;
	is_valid = is_valid && (
		(is_31_day_month(d.month()) && d.day() < 32) ||
		(is_30_day_month(d.month()) && d.day() < 31) ||
		(d.month() == 2 && (is_leap(d) && d.day() < 30) || d.day() < 29)
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
	case 2:
	{
		if (is_leap(*this))
			d = next_val(29, d);
		else
			d = next_val(28, d);
		break;
	}
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		d = next_val(31, d);
		break;
	default:
		d = next_val(30, d);
	}

	// handles case when next day is the first day of next month
	if (d == 1)
	{
		m = next_val(12, m);
		if (m == 1)
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

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

int main()
{

	try
	{
		Date today{ 1978, 6,26 };
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