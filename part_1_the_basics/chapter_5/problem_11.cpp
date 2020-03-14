//
// Created by Nikita Elsakov on 14.03.2020.
//
//	This program calculates first N Fibonacci numbers
//

#include <iostream>
#include <vector>

std::vector<int32_t> calculateFibonacci(int32_t n)
{
	std::vector<int32_t> fibonacciSeries;
	int32_t prev = 1;
	int32_t current = 1;
	while (fibonacciSeries.size() != n)
	{
		int32_t next = prev + current;
		fibonacciSeries.push_back(next);
		prev = current;
		current = next;
	}
	return fibonacciSeries;
}

int main()
{
	std::cout << "How many Fibonacci numbers needs to be found:\n";
	auto n = 0;
	std::cin >> n;
	auto series = calculateFibonacci(n);
	bool isNegativeNumFound = false;
	auto maxFibonacciThatFitsInInt = 0;
	for (auto it = series.begin(); it < series.end(); ++it)
	{
		if (*it < 0 && not isNegativeNumFound)
		{
			isNegativeNumFound = true;
			maxFibonacciThatFitsInInt = *(it - 1);
		}
		std::cout << *it << ' ';
	}
	std::cout << "\nMax Fibonacci number that fits into 32 bit integer is: "
			  << maxFibonacciThatFitsInInt << '\n';
	return 0;
}

