//
// Created by Nikita Elsakov on 06.03.2020.
// This program converts digits into spelled-out values and spelled-out values into digits
// This is a slightly modified version, because it works with any
// number or spelled-out values. In the book it was required to use single loop
// to convert single digit into spelled-out value and convert spelled-out value
// to digit
//

#include "problem_6.h"

std::string convertInput(const std::string& input)
{
	if (isNumber(input))
		return convertNumberToString(input);
	else
		return convertStringToNumbers(input);
}

void prompt(std::string& input)
{
	std::cout << "Enter a number or string that represents a numbers and press enter.\n"
		<< "E.g. 4583 or four five eight three:\n";
	std::getline(std::cin, input);
}

int main()
{
	std::string input{};
	prompt(input);
	std::cout << convertInput(input) << std::endl;
	return 0;
}

