//
// Created by Nikita Elsakov on 07.03.2020.
// Can perform arithmetic operations on two numbers from 0 to 9
// Numbers can be spelled-out values. E.g. one two + or 1 2 +
//

#include "problem_6.h"
#include <cstdlib>
#include <fstream>

int main()
{
	const std::vector<std::string> spelledDigits{ "zero", "one", "two", "three", "four", "five",
												  "six", "seven", "eight", "nine", "dot" };
	constexpr char outfile[] = "out.txt";
	std::cout << "Enter two numbers from 0 to 9"
			  << " (or spelled-out values) followed by operation sign.\n"
			  << "E.g. '1 2 +' or 'one two +':\n";
	std::string input{};
	std::getline(std::cin, input);
	auto parts = splitString(input);
	std::string a = "";
	std::string b = "";
	auto operation = ' ';
	if (isNumber(parts.at(0)))
		a = parts.at(0);
	else
		a = convertStringToNumbers(parts.at(0), spelledDigits);
	if (isNumber(parts.at(1)))
		b = parts.at(1);
	else
		b = convertStringToNumbers(parts.at(1), spelledDigits);
	operation = parts.at(2)[0];
	std::ofstream(outfile) << a << ' ' << b << ' ' << operation;
	auto result = std::system(std::string("./p1c3pr5 < " + std::string(outfile)).c_str());
	std::cout << "Process finished with code: " << result << std::endl;
	return 0;
}

