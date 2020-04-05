// Rev 1. Complement exercise 14 of chapter 9

#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <string>

class Money
{
public:
	Money(long cents);
	Money(const std::string& money);
	long get_cents() const { return cents; }
private:
	long cents;
};

bool is_money_valid(const std::string& money);
long str_to_cents(const std::string& money);
std::ostream& operator<<(std::ostream& os, const Money& m);
Money operator+(const Money& lhs, const Money& rhs);
Money operator-(const Money& lhs, const Money& rhs);
Money operator*(const Money& lhs, double rhs);
Money operator/(const Money& lhs, double rhs);

#endif // !MONEY_H
