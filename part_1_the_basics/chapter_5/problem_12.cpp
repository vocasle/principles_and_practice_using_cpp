//
// Created by Nikita Elsakov on 14.03.2020.
//
// This is an implementation of "Bulls and Cows"
//

#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include <ciso646>
#include <regex>

void printIntro()
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
}

bool isInputValid(const std::string& input)
{
	std::regex regex("\\d\\d\\d\\d");
	return std::regex_match(input.begin(), input.end(), regex);
}

std::vector<int32_t> getReferenceNumbers(int32_t length)
{
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<int32_t> uniformIntDistribution(0, 9);
	std::vector<int32_t> numbers;
	while (numbers.size() != length)
	{
		auto number = uniformIntDistribution(engine);
		if (std::find(numbers.begin(), numbers.end(), number) == numbers.end())
			numbers.push_back(number);
	}
	return numbers;
}
std::vector<int32_t> getGuessedNumbers(const int digits)
{
	std::string input{};
	while (not isInputValid(input))
	{
		std::cout << "Enter 4 numbers from 0 to 9:\n";
		std::cin >> input;
	}
	std::vector<int32_t> guessedNumbers;
	guessedNumbers.reserve(digits);
	for (auto i = 0; i < digits; ++i)
		guessedNumbers.push_back(input[i] - '0');
	return guessedNumbers;
}

bool isGuessCorrect(const int length, const std::vector<int32_t>& referenceNumbers)
{
	auto guessedNumbers = getGuessedNumbers(length);
	auto bulls = 0;
	auto cows = 0;
	for (auto i = 0; i < length; ++i)
	{
		if (guessedNumbers[i] == referenceNumbers[i])
			++bulls;
		else
		{
			for (auto j = 0; j < length; ++j)
			{
				if (j == i)
					continue;
				else if (referenceNumbers[i] == guessedNumbers[j])
					++cows;
			}
		}
	}

	std::cout << "Bulls: " << bulls
			  << ", Cows: " << cows << '\n';
	return bulls == length;
}

int main()
{
	printIntro();
	constexpr const auto digits = 4;
	constexpr const auto limit = 15;
	auto wantsToPlay = true;
	while (wantsToPlay)
	{
		std::vector<int32_t> numbers = getReferenceNumbers(digits);
		bool hasWon = false;
		auto numOfTries = 0;
		while (not hasWon)
		{
			if (numOfTries > limit)
				break;
			hasWon = isGuessCorrect(digits, numbers);
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
		std::cout << "Do you want to try again (y/n)? ";
		char answer = 'y';
		std::cin >> answer;
		wantsToPlay = answer == 'y';
	}
	return 0;
}

