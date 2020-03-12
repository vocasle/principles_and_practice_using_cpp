//
// Created by Nikita Elsakov on 09.03.2020.
//
// This program solves quadratic equations
// ax^2 + bx + c = 0
//
// It uses following formula
//
// x1 = ( - b + sqrt(b^2 - 4ac) ) / 2a
// x2 = ( - b - sqrt(b^2 - 4ac) ) / 2a
//

#include <iostream>
#include <cmath>
#include <stdexcept>

int main()
{
	double a = 0;
	double b = 0;
	double c = 0;
	std::cout << "This program solves quadratic equations."
			  << "ax^2 + bx + c = 0\n"
			  << "Enter coefficients bellow.\n";
	std::cout << "a: ";
	std::cin >> a;
	std::cout << "b: ";
	std::cin >> b;
	std::cout << "c: ";
	std::cin >> c;
	double discriminant = b * b - 4 * a * c;
	auto x1 = 0;
	auto x2 = 0;
	if (discriminant < 0)
		throw std::runtime_error("Discriminant cannot be less than zero!");
	else if (discriminant == 0)
		x1 = x2 = -b / 2 * a;
	else
	{
		x1 = (-b - std::sqrt(discriminant)) / 2 * a;
		x2 = (-b + std::sqrt(discriminant)) / 2 * a;
	}
	std::cout << "x1: " << x1
			  << ", x2: " << x2 << std::endl;
	return 0;
}

