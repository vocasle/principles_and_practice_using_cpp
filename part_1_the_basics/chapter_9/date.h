#include <string>
#include <iostream>

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
public:
	Date(int y, Month m, int d); // check for valid date and initialize
	Month month() const { return m; }
	int day() const { return d; }
	int year() const { return y; }
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