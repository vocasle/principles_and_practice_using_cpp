//
// Created by Nikita Elsakov on 07.03.2020.
//

#ifndef PRINCIPLES_AND_PRACTICE_USING_CPP_PART_1_THE_BASICS_CHAP_3_PROBL_6_H
#define PRINCIPLES_AND_PRACTICE_USING_CPP_PART_1_THE_BASICS_CHAP_3_PROBL_6_H
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

std::vector<std::string> spelledDigits{ "zero", "one", "two", "three", "four", "five",
											"six", "seven", "eight", "nine", "dot" };

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

std::string convertNumberToString(const std::string& input)
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

std::string convertStringToNumbers(const std::string& input)
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
#endif //PRINCIPLES_AND_PRACTICE_USING_CPP_PART_1_THE_BASICS_CHAP_3_PROBL_6_H
