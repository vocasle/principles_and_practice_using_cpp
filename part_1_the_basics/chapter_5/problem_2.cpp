//
// Created by Nikita Elsakov on 12.03.2020.
//

#include <iostream>
#include <stdexcept>

double ctok(double c)
// converts Celsius to Kelvin
{
	constexpr const double absoluteZero = -273.15;
	if (c < absoluteZero)
		throw std::runtime_error(
			"Temperature cannot be below absolute zero. Provided: " + std::to_string(c));
	return c + 273.15;
}

int main()
{
	double c = 0;// declare input variable
	std::cin >> c;// retrieve temperature to input variable
	double k = ctok(c);// convert temperature
	std::cout << k << '\n';// print out temperature
	return 0;
}

