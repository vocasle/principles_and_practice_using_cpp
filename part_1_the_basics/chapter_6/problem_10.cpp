//
// Created by Nikita Elsakov on 23.03.2020.
//
// Solution for problem 10 of chapter 6
//
// The programs prompts a user for two numbers.
// After that it should prompt a user to chose between permutations
// or combinations.
// After that program should print the result of computation to stdout.

#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

int factorial(int32_t a)
{
	if (a < 0)
		error("factorial is not defined for negative numbers");
	uint32_t factorial = 1;
	if (a != 0)
	{
		for (int i = 1; i < a; ++i)
			factorial *= i;
	}
	return factorial;
}

double permutations(int32_t a, int32_t b)
{
	if (a < b)
		error(
			"Permutation formula is: P(a,b) = a! / (a - b)!\nDifference (a - b) in denominator must be greater or equal to zero. Factorial is not defined for negative numbers.");
	return double(factorial(a)) / factorial(a - b);
}

double combinations(int32_t a, int32_t b)
{
	if (a < b)
		std::cerr << "Combination formula is: C(a,b) = P(a,b) / b!\n";
	return permutations(a, b) / factorial(b);
}

bool isValidNumber(const std::string& n)
{
	std::regex regex("\\d+");
	return std::regex_match(n, regex);
}

std::string readNumber()
{
	std::string input{};
	std::cin >> input;
	while (!isValidNumber(input))
	{
		std::cerr << input << " is not a valid number.\n";
		std::cin >> input;
	}
	return input;
}

char promptCalculationType()
{
	std::cout << "Would you like to calculate permutations (P) or combinations (C)? ";
	char answer = ' ';
	while (true)
	{
		std::cin >> answer;
		if (answer == 'P' || answer == 'C')
			break;
		else
			std::cerr << answer << " is not a valid choice. The valid choices are: P or C\n";
		std::cin.rdbuf();
	}
	return answer;
}

int main()
{
	int32_t a = 0;
	int32_t b = 0;
	std::cout << "Enter two numbers a and b:\n"
			  << "a: ";
	a = std::stoi(readNumber());
	std::cout << "b: ";
	b = std::stoi(readNumber());

	auto answer = promptCalculationType();
	int32_t result = 0;
	if (answer == 'P')
		result = permutations(a, b);
	else
		result = combinations(a, b);
	std::cout << answer << "(" << a << ", " << b << ") = " << result << '\n';
	return 0;
}

