//
// Created by Nikita Elsakov on 05.03.2020.
// This program finds a median of entered numbers
//
#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
	std::vector<double> temps;
	for (double temp; std::cin >> temp;)
	{
		temps.push_back(temp);
	}
	std::sort(temps.begin(), temps.end());
	if (temps.size() % 2 == 0)
	{
		std::cout << (temps.at(temps.size() / 2) + temps.at((temps.size() / 2) - 1)) / 2 << std::endl;
	}
	else
	{
		std::cout << temps.at(temps.size() / 2) << std::endl;
	}
	return 0;
}