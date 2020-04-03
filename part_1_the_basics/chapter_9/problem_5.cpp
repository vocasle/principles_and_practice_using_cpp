#include "book.h"
#include <iostream>

int main()
{
	try
	{
		Book book{
		"2354-3423-2532-A",
		"The Fellowship of the Ring",
		"J. R. R. Tolkien",
		Date(1954, Month::jul, 29),
		false
		};

		std::cout << "ISBN: "
			<< book.get_isbn()
			<< "\nTitle: " << book.get_title()
			<< "\nAuthor: " << book.get_author()
			<< "\nCopyright date: " << book.get_copyright_date()
			<< "\nStatus: " << (book.is_checked_out() ? "checked out" : "checked in")
			<< '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}