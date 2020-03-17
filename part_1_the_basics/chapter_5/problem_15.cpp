//
// Created by Nikita Elsakov on 16.03.2020.
//
// This program implements solution for problem 15 of chapter 5

#include <regex>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

bool isInputValid(const std::string& input)
{
	const std::regex regex(R"(\w+\s-\d+|\w+\s\d+)");
	return std::regex_search(input.begin(), input.end(), regex);
}

bool isDayValid(const std::string& input)
{
	constexpr const char* validDays[]{
		"Monday", "monday", "Mon",
		"Tuesday", "tuesday", "Tue",
		"Wednesday", "wednesday", "Wed",
		"Thursday", "thursday", "Thu",
		"Friday", "friday", "Fri",
		"Saturday", "saturday", "Sat",
		"Sunday", "sunday", "Sun"
	};
	for (auto&& day : validDays)
	{
		if (day == input)
			return true;
	}
	return false;
}

int main()
{
	std::cout << "Enter day value pairs, e.g. Monday 5.\n"
			  << "To terminate input type . and press enter.\n";

	std::vector<std::string> days{};
	std::vector<int32_t> values{};
	std::string input{};
	int32_t rejectedInputs = 0;

	for (; std::getline(std::cin, input);)
	{
		if (not isInputValid(input))
		{
			if (input == ".")
				break;
			std::cerr << input << " is not valid.\n";
			++rejectedInputs;
		}
		else
		{
			auto day = input.substr(0, input.find(' '));
			if (not isDayValid(day))
			{
				std::cerr << day << " is not a valid day.\n";
				++rejectedInputs;
			}
			else
			{
				auto value = std::stoi(input.substr(day.length() + 1, input.size()));
				values.push_back(value);
				days.push_back(day);
			}
		}
	}

	std::stringstream ss;
	int32_t sum = 0;
	for (auto&& day : days)
		ss << day;
	for (auto&& value : values)
		sum += value;

	std::cout << ss.str() << '\n'
			  << sum << '\n'
			  << "Number of rejected values: " << rejectedInputs << '\n';
	return 0;
}

