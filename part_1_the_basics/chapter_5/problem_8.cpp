//
// Created by Nikita Elsakov on 13.03.2020.
//
// This program finds a sum of first N numbers
//

#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>

bool isInteger(const std::string& value)
{
	bool isInteger = true;
	for (auto&& c : value)
		isInteger = isInteger && std::isdigit(c);
	return isInteger;
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
	std::cout << "Please enter some integers (press '|' to stop):\n";
	std::vector<int32_t> numbers;
	for (; std::cin >> input;)
	{
		if (input == exitChar)
			break;
		if (isInteger(input))
			numbers.push_back(std::stoi(input));
		else
			throw std::runtime_error("'" + input + "' is not an integer");
	}
	if (n > numbers.size())
		throw std::runtime_error("Number of values (" + std::to_string(n)
			+ ") is less than number of entered integers ("
			+ std::to_string(numbers.size()) + ").");
	int32_t sum = 0;
	for (auto it = numbers.begin(); it != (numbers.begin() + n); ++it)
		sum += *it;
	std::cout << "Sum of first " << n
			  << " integers is: " << sum << '\n';
	return 0;
}

