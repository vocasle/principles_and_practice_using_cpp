#include "book.h"
#include "patron.h"
#include "library.h"

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
		Library lib{};
		lib.add_patron(patron);
		lib.add_book(book);

		Date today{};
		today.add_day(1);
		std::cout << "Today's date: "
			<< today
			<< "\nNext workday is: "
			<< next_workday(today)
			<< "\nCurrent week is: "
			<< week_of_year(today)
			<< "\nNext workday week will be: "
			<< week_of_year(next_workday(today))
			<< '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}