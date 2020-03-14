//
// Created by Nikita Elsakov on 13.03.2020.
//
// This program finds a sum of first N numbers
//

#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <regex>

bool isDouble(const std::string& value)
{
	std::regex regex("\\d*\\.\\d*|\\d*");
	return std::regex_match(value.begin(), value.end(), regex);
}

int main()
{
	constexpr const char* exitChar = "|";
	std::cout << "Please enter the number of values you want to sum:\n";
	int32_t n = 0;
	std::cin >> n;
	if (not std::cin || n < 0)
		throw std::runtime_error("Number of values must be a positive integer!");
	std::string input = "";
	// flush cin
	std::getline(std::cin, input);
	std::cout << "Please enter some real numbers (press '|' to stop):\n";
	std::vector<double> numbers;
	for (; std::cin >> input;)
	{
		if (input == exitChar)
			break;
		if (isDouble(input))
			numbers.push_back(std::stod(input));
		else
			throw std::runtime_error("'" + input + "' is not a real number");
	}
	if (n > numbers.size())
		throw std::runtime_error("Number of values (" + std::to_string(n)
			+ ") is less than number of entered real numbers ("
			+ std::to_string(numbers.size()) + ").");
	double sum = 0;
	for (auto it = numbers.begin(); it != (numbers.begin() + n); ++it)
		sum += *it;
	std::cout << "Sum of first " << n
			  << " real numbers is: " << sum
			  << "\nAdjacent differences:\n";
	for (auto it = numbers.begin() + 1; it != numbers.end(); ++it)
	{
		std::cout << *it - *(it - 1) << ' ';
	}
	std::cout << std::endl;
	return 0;
}

