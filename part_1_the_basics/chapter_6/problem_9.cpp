//
// Created by Nikita Elsakov on 23.03.2020.
//
// Solution for problem 9 of chapter 6

#include <iostream>
#include <string>

int main()
{
	std::string number{};
	std::cout << "Enter any number from 1 to 9999:\n";
	std::cin >> number;
	auto size = number.size();
	switch (size)
	{
	case 4:
		std::cout << number.at(size - 4) << " thousand and ";

	case 3:
		std::cout << number.at(size - 3) << " hundred and ";

	case 2:
		std::cout << number.at(size - 2) << " tens and ";

	case 1:
		std::cout << number.at(size - 1) << " ones.\n";
		break;
	default:
		std::cerr << number << " is out of 0..9999 range.\n";
	}

	return 0;
}

