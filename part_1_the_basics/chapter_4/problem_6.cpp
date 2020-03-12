//
// Created by Nikita Elsakov on 06.03.2020.
// This program converts digits into spelled-out values and spelled-out values into digits
// This is a slightly modified version, because it works with any
// number or spelled-out values. In the book it was required to use single loop
// to convert single digit into spelled-out value and convert spelled-out value
// to digit
//

#include "problem_6.h"

int main()
{
	std::vector<std::string> spelledDigits{ "zero", "one", "two", "three", "four", "five",
											"six", "seven", "eight", "nine", "dot" };
	std::cout << "Enter a number or string that represents a numbers and press enter.\n"
			  << "E.g. 4583 or four five eight three:\n";
	auto input = std::string();
	std::getline(std::cin, input);
	if (isNumber(input))
		std::cout << convertNumberToString(input, spelledDigits) << std::endl;
	else
		std::cout << convertStringToNumbers(input, spelledDigits) << std::endl;
	return 0;
}

