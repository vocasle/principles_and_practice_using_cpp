//
// Created by Nikita Elsakov on 08.03.2020.
// This program calculates prime numbers
//
#include <iostream>
#include <vector>
#include <chrono>

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<int64_t> primes{ 2 };
	std::cout << "How much primes you want to find:\n";
	auto n = 0;
	std::cin >> n;
	int64_t number = 3;
	while (primes.size() < n)
	{
		auto isPrime = true;
		for (auto&& prime : primes)
		{
			if (not isPrime)
				break;
			isPrime = isPrime && number % prime != 0;
		}
		if (isPrime)
			primes.push_back(number);
		++number;
	}

	for (auto&& prime: primes)
	{
		std::cout << prime << ' ';
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "\nTime consumed: " << duration.count() / 1000000.0 << " seconds." << std::endl;
	return 0;
}

