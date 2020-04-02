// This file contains solution for drill 3 of chapter 9

#include <iostream>
#include <stdexcept>
#include <sstream>

class Date {
	int y, m, d; // year, month, day
public:
	Date(int y, int m, int d); // check for valid date and initialize
	void add_day(int n); // increase the Date by n days
	int month() { return m; }
	int day() { return d; }
	int year() { return y; }
};

Date::Date(int y, int m, int d) : y{ y }, m{ m }, d{ d } { }

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

bool is_valid(Date& d)
{
	bool is_valid = d.year() > 0 && (d.month() > 0 && d.month() < 13) && d.day() > 0;
	is_valid = is_valid && (
		((d.month() == 1 || d.month() == 3 || d.month() == 5 || d.month() == 7 || d.month() == 8 || d.month() == 10 || d.month() == 12) && d.day() < 32) ||
		((d.month() == 4 || d.month() == 6 || d.month() == 9 || d.month() == 11) && d.day() < 31) ||
		(d.month() == 2 && (is_leap(d) && d.day() < 30) || d.day() < 29)
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