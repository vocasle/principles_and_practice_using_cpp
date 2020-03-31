// This file contains solution for problem 4 of chapter 8

#include "problem_3.h"
#include <iostream>

int main()
{
	auto fn_1 = 0;
	auto fn_2 = 1;
	auto n = 3;
	auto max_int = 0;

	while (true)
	{
		std::cout << "Checking for n=" << n << '\n';

		std::vector<int32_t> fib_seq;
		fibonacci(fn_1, fn_2, fib_seq, n);

		if (fib_seq.at(fib_seq.size() - 1) < 0)
		{
			for (auto it = (fib_seq.end() - 1); it != fib_seq.begin(); --it)
			{
				if (*it > 0)
				{
					max_int = *it;
					break;
				}
			}
			break;
		}
		++n;
	}


	std::cout << "Max int: " << max_int << std::endl;
	return 0;
}