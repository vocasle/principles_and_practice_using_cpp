#include "date.h"
#include <stdexcept>
#include <sstream>
#include <ctime>

// ---------------------------------------------------------------
// implementation specific functions and structs
// ---------------------------------------------------------------

struct DaysInYear
{
	int year;
	int days;
	DaysInYear(int year, int days) : year{year}, days{days} { }
};

// returns current year and number of days since jan/1/current year 
// until current month/current day/current year
DaysInYear days_since_jan(long days)
{
	auto year = 1970;
	auto d{ days };
	while (true)
	{
		auto threshold = leapyear(year) ? 366 : 365;
		if (d < threshold)
			break;
		d -= threshold;
		++year;
	}
	return DaysInYear(year, d);
}

int* days_in_months(int year)
{
	static auto days_in_feb = leapyear(year) ? 29 : 28;
	static int days_in_months[]{ 31, days_in_feb, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return days_in_months;
}

// returns amount of days from jan/1/1970 until jan/1/year
long days_untill_year(uint32_t year)
{
	long days{ 0 };
	int y{ 1970 };
	while (y != year)
	{
		auto days_in_the_year = leapyear(y) ? 366 : 365;
		days += days_in_the_year;
		++y;
	}
	return days;
}

// returns amount of days from jan/1/year until month/1/year
long days_untill_month(Month month, uint32_t year)
{
	long days{ 0 };
	int* months = days_in_months(year);
	for (size_t i = 0; i < (size_t(month) - 1); ++i)
	{
		days += months[i];
	}
	return days;
}

bool is_30_day_month(Month m)
{
	return m == Month::apr || m == Month::jun || m == Month::sep || m == Month::nov;
}

bool is_31_day_month(Month m)
{
	return m != Month::feb && !is_30_day_month(m);
}

// ---------------------------------------------------------------
// Date class methods definitions
// ---------------------------------------------------------------

Date::Date(uint32_t year, Month month, uint32_t day) : days{0}
{
	if (!is_date(year, month, day))
	{
		error("Error in Date::Date() - (" + std::to_string(year)
			+ ","
			+ std::to_string(int(month)) 
			+ ","
			+ std::to_string(day)
			+ ") is not a valid date."
		);
	}
	days += days_untill_year(year) + days_untill_month(month, year) + day - 1;
}

Date::Date()
	: days{ 0 } {}

int Date::year() const
{
	return days_since_jan(days).year;
}

int Date::day() const
{
	// we add one more day, because Date::days holds
	// number of days since 1/1/1970 until current month/current day/current year
	auto d = days_since_jan(days).days;
	auto md = days_untill_month(month(), year());
	return d - md + 1;
}

Month month_of_day(DaysInYear days_in_year)
{
	auto d = days_in_year.days;
	auto y = days_in_year.year;
	auto months = days_in_months(y);
	auto leap_additive = leapyear(y) ? 1 : 0;
	if (d < 31)
		return Month::jan;
	else if (d < 59 + leap_additive)
		return Month::feb;
	else if (d < 90 + leap_additive)
		return Month::mar;
	else if (d < 120 + leap_additive)
		return Month::apr;
	else if (d < 151 + leap_additive)
		return Month::may;
	else if (d < 181 + leap_additive)
		return Month::jun;
	else if (d < 212 + leap_additive)
		return Month::jul;
	else if (d < 243 + leap_additive)
		return Month::aug;
	else if (d < 273 + leap_additive)
		return Month::sep;
	else if (d < 304 + leap_additive)
		return Month::oct;
	else if (d < 334 + leap_additive)
		return Month::nov;
	else
		return Month::dec;
}

Month Date::month() const
{
	auto m = month_of_day(days_since_jan(days));
	return m;
}

void Date::add_year(uint32_t n)
{
	for (size_t i = 0; i < n; ++i)
		days += 365;
}

void Date::add_month(uint32_t n)
{
	auto years_to_add = int(std::floor(n / 12.0));
	auto months_to_add = n % 12;
	if (years_to_add > 0)
		add_year(years_to_add);
	auto months = days_in_months(year());
	while (months_to_add > 0)
	{
		days += months[int(month()) - 1];
		--months_to_add;
	}
}

void Date::add_day(uint32_t n)
{
	days += n;
}

// --------------------------------------------------
// helper functions
// --------------------------------------------------


bool leapyear(int year)
{
	return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
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

bool is_date(uint32_t year, Month month, uint32_t day)
{
	bool is_valid = year >= 1970;
	bool is_bad_day = day == 0 ||
		(
			(is_30_day_month(month) && day > 30) ||
			(is_31_day_month(month) && day > 31) ||
			(month == Month::feb && 
				((leapyear(year) && day > 29) || (!leapyear(year) && day > 28)))
			);
	is_valid = is_valid && !is_bad_day;
	return is_valid;
}

std::istream& operator>>(std::istream& is, Date& dd)
{
	int y, m, d;
	char ch1, ch2, ch3, ch4;
	is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
	if (!is) return is;
	if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') { // oops: format error
		is.clear(std::ios_base::failbit); // set the fail bit
		return is;
	}
	dd = Date(y, Month(m), d); // update dd
	return is;
}

bool operator==(const Date& lhs, const Date& rhs)
{
	return lhs.day() == rhs.day() && lhs.month() == rhs.month() && lhs.year() == rhs.year();
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs == rhs);
}