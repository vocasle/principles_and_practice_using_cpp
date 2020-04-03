//
// Created by Nikita Elsakov on 24.02.2020.
//
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <ciso646>

bool isValid(const std::string& s)
{
	return s == "cm" || s == "m" || s == "in" || s == "ft";
}

double toMeters(double length, const std::string& unit)
{
	constexpr double kToMeter = 0.01;
	constexpr double kToCm = 2.54;
	constexpr double kToIn = 12;
	if (unit == "m")
		return length;
	else if (unit == "cm")
		return length * kToMeter;
	else if (unit == "in")
		return length * kToCm * kToMeter;
	else if (unit == "ft")
		return length * kToIn * kToCm * kToMeter;
	else
		throw std::invalid_argument(std::to_string(length) + " is not a valid unit");
}

int main()
{
	double largest{ INT_MIN };
	std::string largestUnit = "m";
	double smallest{ INT_MAX };
	std::string smallestUnit = "m";
	std::vector<double> lengths{};

	while (true)
	{
		std::string input{};
		std::cout << "enter an integer with unit character and press 'enter':\n";
		std::getline(std::cin, input);
		if (input == "|")
			break;
		std::string digits{};
		for (auto&& c : input)
		{
			if (std::isdigit(c) || c == '.')
				digits += c;
		}
		auto length = std::stod(digits);
		std::string unit = input.substr(digits.length(), input.length() - digits.length());
		if (not isValid(unit))
		{
			std::cerr << "unit '" << unit << "' is not supported!";
			return EXIT_FAILURE;
		}
		lengths.push_back(toMeters(length, unit));
		if (toMeters(largest, largestUnit) < toMeters(length, unit))
		{
			largest = length;
			largestUnit = unit;
		}
		if (toMeters(smallest, smallestUnit) > toMeters(length, unit))
		{
			smallest = length;
			smallestUnit = unit;
		}
		std::cout << smallest << smallestUnit << " smallest so far\n";
		std::cout << largest << largestUnit << " largest so far\n";
	}
	std::cout << "numbers entered: " << lengths.size() << '\n';
	std::cout << "total sum in meters: " << std::accumulate(lengths.begin(), lengths.end(), 0.0) << '\n';
	std::cout << "list of lengths in meters:\n";
	std::sort(lengths.begin(), lengths.end());
	std::for_each(lengths.begin(), lengths.end(), [](double d)
	{
	  std::cout << d << ' ';
	});
	std::cout << '\n';
	std::cout << smallest << smallestUnit << " smallest so far\n";
	std::cout << largest << largestUnit << " largest so far\n";
	return EXIT_SUCCESS;
}
