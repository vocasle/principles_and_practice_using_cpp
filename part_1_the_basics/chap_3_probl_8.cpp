//
// Created by Nikita Elsakov on 07.03.2020.
// This program calculates number of squares on chess bord needed
// to give amount of rice, e.g. 1000, 1000000, etc.
//

#include <iostream>
#include <cmath>

int main()
{
	std::cout << "Enter amount of rice you need and press enter:\n";
	auto amount = 0;
	constexpr auto numOfSquares = 64;
	std::cin >> amount;
	auto sum = 0;
	auto cnt = 0;
	for (; cnt < numOfSquares; ++cnt)
	{
		if (sum >= amount)
			break;
		sum += std::pow(2, cnt);
		std::cout << "Square: " << cnt
				  << ", number of rice grains: " << sum << "\n";
	}
	std::cout << "You need " << cnt
			  << " squares to get " << amount << " of rice grains.\n"
			  << "You will get " << sum << " rice grains\n";

	return 0;
}

