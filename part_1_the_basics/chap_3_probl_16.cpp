//
// Created by Nikita Elsakov on 08.03.2020.
// This program finds the mode of the sequence of numbers
//

#include "chap_3_probl_16.h"

int main()
{
	std::cout << "Enter sequence of numbers separated by space."
			  << "\nTo terminate the input enter '.' and press 'enter':\n";

	std::vector<int> numbers;
	for (auto i = 0; std::cin >> i;)
		numbers.push_back(i);
	std::cout << "The mode is: " << findMode(numbers) << std::endl;
	return 0;
}

