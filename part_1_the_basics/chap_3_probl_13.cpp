//
// Created by Nikita Elsakov on 08.03.2020.
// Finds prime numbers between 1 and 100 using "Sieve of Eratosthenes"
//

#include <iostream>
#include <vector>

int main()
{
	std::vector<int> primes;
	for (auto i = 2; i < 101; ++i)
		primes.push_back(i);

	for (auto it = primes.begin(); it != primes.end();)
	{
		auto next = it++;
		for (;;)
		{
			if (*next != *it && *next % *it == 0)
				primes.erase(next);
			if (next == primes.end())
				break;
			++next;
		}
	}

	for (auto&& prime : primes)
		std::cout << prime << ' ';
	std::cout << std::endl;
	return 0;
}
