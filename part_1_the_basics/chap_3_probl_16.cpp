//
// Created by Nikita Elsakov on 08.03.2020.
// This program finds the mode of the sequence of numbers
//

#include <iostream>
#include <vector>
#include <map>

int main()
{
	std::cout << "Enter sequence of numbers separated by space."
			  << "\nTo terminate the input enter '.' and press 'enter':\n";

	std::vector<int> numbers;
	for (auto i = 0; std::cin >> i;)
		numbers.push_back(i);
	std::map<int, int> occurrences;
	for (auto&& number : numbers)
		occurrences[number]++;
	auto mode = 0;
	auto numOfRepeats = 0;
	for (auto&& occurrence : occurrences)
	{
		if (numOfRepeats < occurrence.second)
		{
			numOfRepeats = occurrence.second;
			mode = occurrence.first;
		}
	}
	std::cout << "The mode is: " << mode << std::endl;
	return 0;
}

