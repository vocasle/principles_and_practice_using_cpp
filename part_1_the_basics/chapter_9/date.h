#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

enum class Weekday
{
	sun, mon, tue, wed, thu, fri, sat
};

class Date {
public:
	Date(); // initialize with current date
	Date(int y, Month m, int d); // check for valid date and initialize
	Month month() const { return m; }
	int day() const { return d; }
	int year() const { return y; }

	void add_day(uint32_t n); // increment current date by n days
	void add_month(uint32_t n); // increment current date by n months
	void add_year(uint32_t n); // increment current date by n years
private:
	int y; // year
	Month m;
	int d; // day
};

bool is_leap(int year);
bool is_30_day_month(Month m);
bool is_31_day_month(Month m);
bool is_valid(const Date& d);
void error(const std::string& msg);
std::ostream& operator<<(std::ostream& os, const Date& d);
const Date& default_date();
Weekday day_of_week(const Date& d);
std::string weekday_name(Weekday wd);
Date next_workday(const Date& d);
int week_of_year(const Date& d);

#endif // !DATE_H
