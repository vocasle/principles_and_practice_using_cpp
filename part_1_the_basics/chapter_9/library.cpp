// This file contains definition of Library's methods and helper functions
// Rev 1: Definition of Library class methods

#include "library.h"

#include <sstream>
#include <algorithm>

void Library::add_book(const Book& book)
{
	books.push_back(book);
}

void Library::add_patron(const Patron& patron)
{
	patrons.push_back(patron);
}

Book Library::checkout_book(const Patron& patron, const Book& book)
{
	auto found_patron = std::find(
		patrons.begin(), patrons.end(), patron
	);
	if (found_patron == patrons.end())
		error("Error in Library::checkout_book() - Patron with name '"
			+ patron.get_name() 
			+ "' is not registered.");
	auto found_book = std::find(
		books.begin(), books.end(), book
	);
	if (found_book == books.end())
	{
		std::stringstream ss;
		ss << book;
		error("Error in Library::checkout_book() - Book with ISBN="
			+ book.get_isbn() + " not found.");
	}
	if (owes_fees(*found_patron))
		error("Error in Library::checkout_book() - "
			+ found_patron->get_name()
			+ " owes fee: "
			+ std::to_string(found_patron->get_fees())
			+ "$.");
	if (found_book->is_checked_out())
		error("Error in Library::checkout_book() - Requested book is already checked out.");
	found_book->check_out();
	transactions.push_back(Transaction{ *found_book, *found_patron, Date{} });
	return *found_book;
}

Book Library::checkout_book(const Patron& patron, const std::string& isbn)
{
	for (const auto& book : books)
		if (book.get_isbn() == isbn)
			return checkout_book(patron, book);
	error("Error in Library::checkout_book() - Book with ISBN="
		+ isbn + " not found.");
}

std::vector<Patron> Library::get_debtors() const
{
	std::vector<Patron> debtors;
	for (const auto& patron : patrons)
		if (owes_fees(patron))
			debtors.push_back(patron);
	return debtors;
}