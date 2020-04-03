//
// Created by Nikita Elsakov on 23.03.2020.
//
// This program implements Bull and Cows games for 4 letter words
// It is used in conjunction with words.txt file, that contains 4 letter words.
// This program must be executed with one argument - path to words.txt file.


#include <iostream>
#include <random>
#include <vector>
#include <regex>
#include <fstream>
#include <ciso646>

void printIntro()
{
	std::cout << "Welcome to Bulls and Cows game!\n"
			  << "Try to guess a 4 letter word.\n"
			  << "For example, 'milk' is a word that you need to guess.\n"
			  << "Let 'meal' will be your first guess. For that guess you will get\n"
			  << "1 bull for guessing right the position and letter (1),\n"
			  << "and 1 cow for guessing wrong the position, but guessing right\n"
			  << "the letter (4).\n"
			  << "You can guess 15 times.\n"
			  << "Good luck!\n";
}

bool isInputValid(const std::string& input)
{
	std::regex regex(R"(\w\w\w\w)");
	return std::regex_match(input.begin(), input.end(), regex);
}

std::string getWord(const std::vector<std::string>& words, int32_t position)
{
	return words.at(position);
}

std::vector<std::string> getWords(const std::string& file)
{
	std::ifstream ifs(file);
	std::vector<std::string> words{};
	std::string word{};
	while (ifs >> word)
		words.push_back(word);
	return words;
}

int32_t getWordPosition()
{
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<int32_t> uniformIntDistribution(0, 2500);
	return uniformIntDistribution(engine);
}
std::string getGuessedWord()
{
	std::string input{};
	while (not isInputValid(input))
	{
		std::cout << "Enter 4 letter word:\n";
		std::cin >> input;
	}
	return input;
}

bool isGuessCorrect(const std::string& referenceWord)
{
	constexpr const int32_t length = 4;
	auto guessedWord = getGuessedWord();
	auto bulls = 0;
	auto cows = 0;
	for (auto i = 0; i < length; ++i)
	{
		if (guessedWord[i] == referenceWord[i])
			++bulls;
		else
		{
			for (auto j = 0; j < length; ++j)
			{
				if (j == i)
					continue;
				else if (referenceWord[i] == guessedWord[j])
					++cows;
			}
		}
	}

	std::cout << "Bulls: " << bulls
			  << ", Cows: " << cows << '\n';
	return bulls == length;
}

int main(int argc, char* argv[])
{
	printIntro();
	auto words = getWords(argv[1]);
	constexpr const auto limit = 15;
	auto wantsToPlay = true;
	while (wantsToPlay)
	{
		auto position = getWordPosition();
		bool hasWon = false;
		auto numOfTries = 0;
		while (not hasWon)
		{
			if (numOfTries > limit)
				break;
			hasWon = isGuessCorrect(getWord(words, position));
			++numOfTries;
		}
		if (not hasWon)
		{
			std::cout << "You lost. The word was: ";
			std::cout << getWord(words, position) << '\n';
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


