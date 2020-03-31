// This file contains solution for problem 10 of chapter 8

#include <iostream>
#include "problem_10.h"

int main()
{
	std::vector<double> dv{
		1,2,3,4,5,6,7,8,356.0
	};

	std::vector<char> cv{
		'A', 'b', '$', '%', 'C', 's'
	};

	try
	{
		auto maxd = maxv(dv);
		auto maxc = maxv(cv);
	
		std::cout << "Max double: " << maxd
			<< "\nMax char: " << maxc << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}