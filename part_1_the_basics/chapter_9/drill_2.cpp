// This file contains solution for drill 2 of chapter 9

#include <iostream>
#include <stdexcept>
#include <sstream>

struct Date
{
	int y; // year
	int m; // month of the year
	int d; // day of month
	Date(int y, int m, int d);
	void add_day(int n);
};


std::ostream& operator<<(std::ostream& os, const Date& d);
bool is_valid(const Date& d);
void error(const std::string& msg);

Date::Date(int y, int m, int d): y{y}, m{m}, d{d}
{
	if (!is_valid(*this))
	{
		std::stringstream ss;
		ss << *this;
		error(ss.str() + " is not a valid date");
	}
}

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
	return os << '(' << d.y
		<< ',' << d.m
		<< ',' << d.d << ')';
}

bool is_leap(const Date& d)
{
	return (d.y % 4 == 0) && ((d.y % 100 != 0) || (d.y % 400 == 0));
}

bool is_30_day_month(int m)
{
	return m == 4 || m == 6 || m == 9 || m == 11;
}

bool is_31_day_month(int m)
{
	return m != 2 && !is_30_day_month(m);
}

bool is_valid(const Date& d)
{
	bool is_valid = d.y > 0 && (d.m > 0 && d.m < 13) && d.d > 0;
	is_valid = is_valid && (
		(is_31_day_month(d.m) && d.d < 32) ||
		(is_30_day_month(d.m) && d.d < 31) ||
		(d.m == 2 && (is_leap(d) && d.d < 30) || d.d < 29)
		);
	return is_valid;
}

int next_val(int threshold, int val)
{
	return val != threshold ? val + 1 : 1;
}

void increment_day(Date& d)
{
	switch (d.m)
	{
	case 2:
	{
		if (is_leap(d))
			d.d = next_val(29, d.d);
		else
			d.d = next_val(28, d.d);
		break;
	}
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		d.d = next_val(31, d.d);
		break;
	default:
		d.d = next_val(30, d.d);
	}

	// handles case when next day is the first day of next month
	if (d.d == 1)
	{
		d.m = next_val(12, d.m);
		if (d.m == 1)
			++d.y;
	}
}

void Date::add_day(int n)
{
	if (n <= 0)
		error("add_day() - negative argument passed");
	for (int i = 0; i < n; ++i)
		increment_day(*this);
}

int main()
{

	try
	{
		Date today{ 1978, 6,26 };
		Date tomorrow = today;
		tomorrow.add_day(1);
		std::cout << today
			<< '\n' << tomorrow << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}