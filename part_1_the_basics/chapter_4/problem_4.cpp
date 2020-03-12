//
// Created by Nikita Elsakov on 05.03.2020.
// This program finds guessed number in 7 attempts
//

#include <iostream>

int getMedian(int begin, int end)
{
	return (begin + end) / 2;
}

int main()
{
	constexpr auto limit = 7;
	auto floor = 0;
	auto ceil = 101;
	auto median = getMedian(floor, ceil);
	std::cout << "Think about an integer between 1 and 100\n";
	for (auto i = 0; i < limit; ++i)
	{
		auto answer = ' ';
		std::cout << "Is " << median << " greater then guessed number?\n";
		std::cin >> answer;
		if (answer == 'y')
			ceil = median;
		else
			floor = median;
		median = getMedian(floor, ceil);
	}
	std::cout << "The number guessed is: " << median << std::endl;

	return 0;
}

