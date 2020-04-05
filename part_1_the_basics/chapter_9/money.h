// Rev 1. Complement exercise 14 of chapter 9
// Rev 2. Complement exercise 15 of chapter 9

#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <string>

class Money
{
public:
	Money(double money, const std::string& currency);
	long get_cents() const { return cents; }
	std::string get_currency() const { return currency; }
private:
	std::string currency;
	long cents;
};

bool is_money_valid(double money);
std::ostream& operator<<(std::ostream& os, const Money& m);
Money operator+(const Money& lhs, const Money& rhs);
Money operator-(const Money& lhs, const Money& rhs);
Money operator*(const Money& lhs, double rhs);
Money operator/(const Money& lhs, double rhs);

#endif // !MONEY_H
