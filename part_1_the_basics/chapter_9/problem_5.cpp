#include "book.h"
#include "patron.h"
#include "library.h"

#include <iostream>

int main()
{
	try
	{
		Date d{ 2020, Month::feb, 29 };
		std::cout << d << std::endl;
		for (auto i = 1; i <= 5; ++i)
		{
			d.add_year(1);
			std::cout << d << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}