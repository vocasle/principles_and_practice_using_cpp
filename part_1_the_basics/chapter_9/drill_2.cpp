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

Date::Date(int y, int m, int d): y{y}, m{m}, d{d} { }

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

bool is_valid(const Date& d)
{
	bool is_valid = d.y > 0 && (d.m > 0 && d.m < 13) && d.d > 0;
	is_valid = is_valid && (
		((d.m == 1 || d.m == 3 || d.m == 5 || d.m == 7 || d.m == 8 || d.m == 10 || d.m == 12) && d.d < 32) ||
		((d.m == 4 || d.m == 6 || d.m == 9 || d.m == 11) && d.d < 31) ||
		(d.m == 2 && (is_leap(d) && d.d < 30) || d.d < 29)
		);
	return is_valid;
}

int next_val(int threshold, int val)
{
	return val != threshold ? val + 1 : 1;
}

void Date::add_day(int n)
{
	if (!is_valid(*this))
	{
		std::stringstream ss;
		ss << *this;
		throw std::runtime_error(ss.str() + " is not a valid date");
	}

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

int main()
{
	Date today{ 1978, 6,26 };
	Date tomorrow = today;

	try
	{
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