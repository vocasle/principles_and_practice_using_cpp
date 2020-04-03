#include "book.h"
#include "patron.h"

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

		Patron patron{ "Nikita Elsakov", "12S4-52D4-2N45-A823", 0 };
		std::cout << (owes_fees(patron) ? "owes" : "does not owe") << std::endl;
		patron.set_fees(25);
		std::cout << (owes_fees(patron) ? "owes" : "does not owe") << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}