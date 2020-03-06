//
// Created by Nikita Elsakov on 06.03.2020.
// This program performs simple calculations
// Subtraction, Division, Multiplication, Summation
//

#include <iostream>
#include <stdexcept>

int main()
{
	auto a = 0.0;
	auto b = 0.0;
	auto result = 0.0;
	auto operation = ' ';
	std::cout << "Enter two real numbers separated"
			  << " by space and followed by operation symbol "
			  << "and press enter. \n"
			  << "E.g. '3.14 3.14 /':\n";
	std::cin >> a >> b >> operation;
	switch (operation)
	{
	case '+':
		result = a + b;
		break;
	case '-':
		result = a - b;
		break;
	case '/':
		result = a / b;
		break;
	case '*':
		result = a * b;
		break;
	default:
		throw std::invalid_argument(std::to_string(operation) + " is not supported!");
	}
	std::cout << a << ' '
			  << operation << ' ' << b
			  << " = " << result << std::endl;
	return 0;
}

