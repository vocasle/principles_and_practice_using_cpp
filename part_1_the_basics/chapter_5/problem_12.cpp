//
// Created by Nikita Elsakov on 14.03.2020.
//
// This is an implementation of "Bulls and Cows"
//
// Revision v2: Move all game logic into Game class.
// Revision v2 is solution for Exercise 11 of chapter 7.
//

#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include <ciso646>
#include <regex>
#include <tuple>

struct GameResult
{
	int32_t bulls;
	int32_t cows;
	GameResult(const int32_t bulls, const int32_t cows) : bulls(bulls), cows(cows) { }
};

class Game
{
public:
	void play();
	bool playerWantsToPlay() const;
	Game();
private:
	bool hasWon() const;
	void printIntro() const;
	bool isInputValid(const std::string& input) const;
	bool hasTries() const;
	std::vector<int32_t> getReferenceNumbers();
	std::vector<int32_t> getGuessedNumbers();
	GameResult getGuess();
	void printGameWon();
	void printGameLost();
	void promptUserToPlayAgain();
	void printGuessResult();
	void resetGame();
private:
	constexpr static const int32_t length = 4;
	constexpr static const int32_t limit = 15;
	int32_t guessCount = 0;
	bool wantsToPlay = true;
	GameResult gameResult;
	std::vector<int32_t> referenceNumbers;
};

void Game::play()
{
	printIntro();
	// while player has not won or limit of retries has not been reached
	while (not hasWon() and hasTries()) // play the game
	{
		gameResult = getGuess();
		++guessCount;
		printGuessResult();
	}
	promptUserToPlayAgain();
	if (wantsToPlay)
		resetGame();
}

void Game::resetGame()
{
	gameResult = GameResult(0, 0);
	guessCount = 0;
	referenceNumbers = getReferenceNumbers();
}

void Game::promptUserToPlayAgain()
{
	hasWon() ? printGameWon() : printGameLost();
	std::cout << "Do you want to try again (y/n)? ";
	char answer = 'y';
	std::cin >> answer;
	wantsToPlay = answer == 'y';
}

void Game::printGuessResult()
{
	std::cout << "Bulls: " << gameResult.bulls
		<< ", Cows: " << gameResult.cows << '\n';
}

bool Game::playerWantsToPlay() const
{
	return wantsToPlay;
}

Game::Game() : referenceNumbers(getReferenceNumbers()), gameResult(0, 0) {}

bool Game::hasWon() const
{
	return gameResult.bulls == length;
}

bool Game::hasTries() const
{
	return guessCount < limit;
}

void Game::printIntro() const
{
	std::cout << "\n\nWelcome to Bulls and Cows game!\n"
		<< "Try to guess 4 integers in range from 0 to 9.\n"
		<< "For example, 1234 is a number that you need to guess.\n"
		<< "Let 1532 will be your first guess. For that guess you will get\n"
		<< "1 bull for guessing right the position and number (1),\n"
		<< "and 1 cow for guessing wrong the position, but guessing right\n"
		<< "the number (3).\n"
		<< "You can guess 15 times.\n"
		<< "Good luck!\n\n";
}

bool Game::isInputValid(const std::string& input) const
{
	std::regex regex(R"(\d\d\d\d)");
	return std::regex_match(input.begin(), input.end(), regex);
}

std::vector<int32_t> Game::getReferenceNumbers()
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

std::vector<int32_t> Game::getGuessedNumbers()
{
	std::string input{};
	while (not isInputValid(input))
	{
		std::cout << "Enter 4 numbers from 0 to 9:\n";
		std::cin >> input;
	}
	std::vector<int32_t> guessedNumbers;
	guessedNumbers.reserve(length);
	for (auto i = 0; i < length; ++i)
		guessedNumbers.push_back(input[i] - '0');
	return guessedNumbers;
}

GameResult Game::getGuess()
{
	auto guessedNumbers = getGuessedNumbers();
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

	return GameResult(bulls, cows);
}

void Game::printGameWon()
{
	std::cout << "Congratulations! You won! You made "
		<< guessCount
		<< " guesses.\n";
}

void Game::printGameLost()
{
	std::cout << "You lost. The number was: ";
	for (auto&& n : referenceNumbers)
		std::cout << n;
	std::cout << '\n';
}

int main()
{
	auto game = Game();
	while (game.playerWantsToPlay())
		game.play();
	return 0;
}

