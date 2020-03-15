//
// Created by Nikita Elsakov on 14.03.2020.
//
// This is an implementation of "Bulls and Cows"
//

#include <iostream>
#include <random>
#include <vector>
#include <sstream>

int main()
{
	std::cout << "Welcome to Bulls and Cows game!\n"
			  << "Try to guess 4 integers in range from 0 to 9.\n"
			  << "For example, 1234 is a number that you need to guess.\n"
			  << "Let 1532 will be your first guess. For that guess you will get\n"
			  << "1 bull for guessing right the position and number (1),\n"
			  << "and 1 cow for guessing wrong the position, but guessing right\n"
			  << "the number (3).\n"
			  << "You can guess 15 times.\n"
			  << "Good luck!\n";
	constexpr const auto digits = 4;
	constexpr const auto limit = 15;
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<int32_t> uniformIntDistribution(0, 9);
	std::vector<int32_t> numbers;
	while (numbers.size() != digits)
	{
		auto number = uniformIntDistribution(engine);
		if (std::find(numbers.begin(), numbers.end(), number) == numbers.end())
			numbers.push_back(number);
	}
	bool hasWon = false;
	auto numOfTries = 0;
	while (not hasWon)
	{
		if (numOfTries > limit)
			break;
		std::cout << "Enter 4 numbers from 0 to 9:\n";
		int32_t guessedNumbers[digits];
		std::string input = "";
		std::cin >> input;
		for (auto i = 0; i < digits; ++i)
			guessedNumbers[i] = input[i] - '0';
		auto bulls = 0;
		auto cows = 0;
		for (auto i = 0; i < digits; ++i)
		{
			if (guessedNumbers[i] == numbers[i])
				++bulls;
			else
			{
				for (auto j = 0; j < digits; ++j)
				{
					if (j == i)
						continue;
					else if (numbers[i] == guessedNumbers[j])
						++cows;
				}
			}
		}
		hasWon = bulls == digits;
		std::cout << "Bulls: " << bulls
				  << ", Cows: " << cows << '\n';
		++numOfTries;
	}
	if (not hasWon)
	{
		std::cout << "You lost. The number was: ";
		std::ostringstream os;
		for (auto&& n : numbers)
			os << n;
		std::cout << os.str() << '\n';
	}
	else
	{
		std::cout << "Congratulations! You won! You tried " << numOfTries
				  << " times.\n";
	}
	return 0;
}

