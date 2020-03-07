//
// Created by Nikita Elsakov on 07.03.2020.
//
// This program allows to play "rock, paper, scissors" game.
//

#include <iostream>
#include <random>

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution distribution(0,2);
	std::cout << "Welcome to \"ROCK, PAPER, SCISSORS\" game!\n"
			  << "The rules are simple. Enter the number that corresponds to"
			  << " either rock, paper or scissors you see on screen and try to"
			  << " beat Computer.\n"
			  << "Good luck.\n";
	constexpr auto maxRepeats = 3;
	constexpr const char* variants[]{ "Rock", "Paper", "Scissors" };
	auto wantsToPlayNextGame = true;
	while (wantsToPlayNextGame)
	{
		auto userScore = 0;
		auto computerScore = 0;
		for (auto i = 0; i < maxRepeats; ++i)
		{
			auto random = distribution(gen);
			std::cout << "Enter the number to try your luck.\n"
					  << "Rock - 0, Paper - 1, Scissors - 2:\n";
			auto userInput = 0;
			std::cin >> userInput;
			if (random == userInput)
			{
				std::cout << "Attempt No. " << i + 1
						  << ". Draw!\n";
				++userScore;
				++computerScore;
			}
			else if ((random == 0 && userInput == 2) || (random == 1 && userInput == 0)
				|| (random == 2 && userInput == 1))
			{
				std::cout << "Attempt No. " << i + 1
						  << ". Computer won this round!\n";
				++computerScore;
			}
			else
			{
				std::cout << "Attempt No. " << i + 1
						  << ". You won this round!\n";
				++userScore;
			}
			std::cout << "Computer: " << variants[random]
					  << ", " << "You: " << variants[userInput] << "\n\n";
		}
		if (userScore > computerScore)
			std::cout << "Congratulations, you won the game!\n";
		else if (userScore == computerScore)
			std::cout << "Nice game. No one won!\n";
		else
			std::cout << "Better luck next time, Computer won the game!\n";
		std::cout << "Your score is: " << userScore
				  << ", Computer's score is: " << computerScore
				  << "\n\nDo you want to try again? (y/n):\n";
		auto answer = ' ';
		std::cin >> answer;
		wantsToPlayNextGame = wantsToPlayNextGame && answer == 'y';
	}
	return 0;
}
