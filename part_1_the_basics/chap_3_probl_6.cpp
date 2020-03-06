//
// Created by Nikita Elsakov on 06.03.2020.
// This program converts digits into spelled-out values and spelled-out values into digits
// This is a slightly modified version, because it works with any
// number or spelled-out values. In the book it was required to use single loop
// to convert single digit into spelled-out value and convert spelled-out value
// to digit
//

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

bool isNumber(const std::string& s)
{
	bool isNumber = true;
	for (auto&& c : s)
		isNumber = isNumber && (std::isdigit(c) || c == '.');
	return isNumber;
}

std::vector<std::string> splitString(const std::string& input)
{
	char delimiter = ' ';
	if (input.find(delimiter) == std::string::npos)
		return std::vector<std::string>{ input };
	std::vector<std::string> result;
	std::string tmp{};
	for (auto&& c : input)
	{
		if (c != delimiter)
			tmp += c;
		else
		{
			result.push_back(tmp);
			tmp = "";
		}
	}
	result.push_back(tmp);
	return result;
}

std::string convertNumberToString(const std::string& input,
	const std::vector<std::string>& spelledDigits)
{
	std::string result{};
	constexpr auto dotPosition = 10;
	for (auto&& c : input)
	{
		if (std::isdigit(c))
			result += spelledDigits.at(c - '0');
		else if (c == '.')
			result += spelledDigits.at(dotPosition);
		else
			throw std::invalid_argument(input + " is not a valid number!");
		result += ' ';
	}
	return result;
}

std::string convertStringToNumbers(const std::string& input,
	const std::vector<std::string>& spelledDigits)
{
	std::string result{};
	for (auto&& s : splitString(input))
	{
		auto it = std::find(spelledDigits.begin(), spelledDigits.end(), s);
		if (it == spelledDigits.end())
			throw std::invalid_argument(s + " is not a spelled number!");
		if (*it == "dot")
			result += '.';
		else
			result += std::to_string(it - spelledDigits.begin());
	}
	return result;
}

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

