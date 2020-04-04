// This file contains solution for exercise 13 of chapter 9.
// In my opinion perfomring operations on rationals is more
// easy than on doubles. Rules for multiplication and division
// are much simpler.

#include "rational.h"

int main()
{
	Rational r{ 2,5 };
	Rational r2{ 7,5 };
	std::cout << r << " + " << r2 << " = " << r + r2 << " (" << (r + r2).to_double() << ")\n";
	std::cout << r << " - " << r2 << " = " << r - r2 << " (" << (r - r2).to_double() << ")\n";
	std::cout << r << " * " << r2 << " = " << r * r2 << " (" << (r * r2).to_double() << ")\n";
	std::cout << r << " / " << r2 << " = " << r / r2 << " (" << (r / r2).to_double() << ")\n";
	std::cout << r << " == " << r2 << " (" << (r == r2 ? "true" : "false") << ")\n";
	std::cout << r << " != " << r2 << " (" << (r != r2 ? "true" : "false") << ")\n";
	std::cout << r << " < " << r2 << " (" << (r < r2 ? "true" : "false") << ")\n";
	std::cout << r << " > " << r2 << " (" << (r > r2 ? "true" : "false") << ")\n";
	return 0;
}