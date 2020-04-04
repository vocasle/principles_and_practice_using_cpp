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
	Date(); // initialize with default date
	Date(uint32_t year, Month month, uint32_t day);  // check for valid date and initialize
	Month month() const;
	int day() const;
	int year() const;

	void add_day(uint32_t n); // increment current date by n days
	void add_month(uint32_t n); // increment current date by n months
	void add_year(uint32_t n); // increment current date by n years
private:
	long days;
};

bool leapyear(int year);
bool is_date(uint32_t y, Month m, uint32_t d);
void error(const std::string& msg);
std::ostream& operator<<(std::ostream& os, const Date& d);
std::istream& operator>>(std::istream& is, Date& dd);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

#endif // !DATE_H
