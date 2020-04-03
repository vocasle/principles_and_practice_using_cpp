#include "book.h"
#include <iostream>

int main()
{
	try
	{
		Book book{
			Genre::fiction,
			"2354-3423-2532-A",
			"The Fellowship of the Ring",
			"J. R. R. Tolkien",
			Date(1954, Month::jul, 29),
			false
		};

		Book book2{
			Genre::fiction,
			"0-395-31555-7",
			"The Two Towers",
			"J. R. R. Tolkien",
			Date(1954, Month::nov, 11),
			false
		};

		std::cout << book << std::endl;
		std::cout << (book == book2 ? "true" : "false") << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}