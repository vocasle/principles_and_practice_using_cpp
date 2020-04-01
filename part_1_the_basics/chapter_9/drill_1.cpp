// This file contains solution for drill 1 of chapter 9

#include <iostream>
#include <stdexcept>
#include <sstream>

struct Date
{
	int y; // year
	int m; // month of the year
	int d; // day of month
};

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

void add_day(Date& dd, int n)
{
	if (!is_valid(dd))
	{
		std::stringstream ss;
		ss << dd;
		throw std::runtime_error(ss.str() + " is not a valid date");
	}

	switch (dd.m)
	{
	case 2:
	{
		if (is_leap(dd))
			dd.d = next_val(29, dd.d);
		else
			dd.d = next_val(28, dd.d);
		break;
	}
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		dd.d = next_val(31, dd.d);
		break;
	default:
		dd.d = next_val(30, dd.d);
	}

	// handles case when next day is the first day of next month
	if (dd.d == 1)
	{
		dd.m = next_val(12, dd.m);
		if (dd.m == 1)
			++dd.y;
	}
}

int main()
{
	Date today;
	today.y = 1978;
	today.m = 6;
	today.d = 25;

	Date tomorrow = today;

	try
	{
		add_day(tomorrow, 1);
		std::cout << today
			<< '\n' << tomorrow << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}