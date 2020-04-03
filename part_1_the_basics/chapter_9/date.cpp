#include "date.h"
#include <stdexcept>
#include <sstream>
#include <ctime>

Date::Date(int y, Month m, int d) : y{ y }, m{ m }, d{ d }
{
	if (!is_valid(*this))
	{
		std::stringstream ss;
		ss << *this;
		error(ss.str() + " is not a valid date");
	}
}

Date::Date()
	: y{ default_date().year() },
	m{ default_date().month() },
	d{ default_date().day() } {}

void Date::add_year(uint32_t n)
{
	if (m == Month::feb && d == 29 && !is_leap(y + n)) // beware of leap years!
	{ 
		m = Month::mar; // use March 1 instead of February 29
		d = 1;
	}
	y += n;
}

void Date::add_month(uint32_t n)
{
	auto years_to_add = int(std::floor(n / 12.0));
	auto months_to_add = n % 12;
	bool day_overflow = (is_30_day_month(m) && d > 30) 
		|| (m == Month::feb && (is_leap(y) && d > 29 || d > 28));
	y += years_to_add;
	auto sum = int(m) + months_to_add;
	if (sum > 12) // month overflow
	{
		++y;
		m = Month(sum - 12);
	}
	else
		m = Month(sum);

	if (day_overflow)
	{
		d = 1;
		add_month(1);
	}
}

int next_val(int threshold, int val)
{
	return val != threshold ? val + 1 : 1;
}

void Date::add_day(uint32_t n)
{
	if (n > 1)
		add_day(n - 1);
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

const Date& default_date()
{
	static const auto time{ std::time(nullptr) };
	static const auto tm{ std::localtime(&time) };
	
	static Date dd{ tm->tm_year + 1900, Month(tm->tm_mon + 1), tm->tm_mday };
	return dd;
}

// calculates the weekday according to 
// https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Implementation-dependent_methods
Weekday day_of_week(const Date& date)
{
	auto d = date.day();
	auto m = int(date.month());
	auto y = date.year();
	d += m < 3 ? y-- : y - 2;
	auto w = (23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
	return Weekday(std::abs(w));
}

std::string weekday_name(Weekday wd)
{
	static const char* weekdays[] {
		 "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
	};
	return weekdays[int(wd)];
}

Date next_workday(const Date& d)
{
	auto wd{ day_of_week(d) };
	auto next_wd_offset{ 0 };

	switch (wd)
	{
	case Weekday::fri:
		next_wd_offset += 3;
		break;
	case Weekday::sat:
		next_wd_offset += 2;
		break;
	default:
		++next_wd_offset;
	}

	auto next_wd{ d };
	next_wd.add_day(next_wd_offset);
	return next_wd;
}

int week_of_year(const Date& d)
{
	auto days{ d.day() };
	for (size_t i = 1; i < int(d.month()); ++i)
	{
		auto month = Month(i);
		if (is_30_day_month(month))
			days += 30;
		else if (is_31_day_month(month))
			days += 31;
		else
			days += is_leap(d.year()) ? 29 : 28;
	}
	// handle first week of the year offset
	Weekday wd_of_jan_1 = day_of_week(Date{ d.year(), Month::jan, 1 });
	days += int(wd_of_jan_1);
	auto a =  int(std::ceil(days / 7.0));
	return a;
}