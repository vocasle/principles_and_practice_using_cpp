// This file contains declaration of Library class
// Rev 1: Declaration of Library class

#ifndef LIBRARY_H
#define LIBRARY_H

#include "patron.h"
#include "book.h"

#include <vector>

struct Transaction
{
	Book book;
	Patron patron;
	Date date;
};

class Library
{
public:
	void add_patron(const Patron& patron);
	void add_book(const Book& book);
	Book checkout_book(const Patron& patron, const Book& book);
	Book checkout_book(const Patron& patron, const std::string& isbn);
	std::vector<Patron> get_debtors() const;
private:
	std::vector<Patron> patrons;
	std::vector<Book> books;
	std::vector<Transaction> transactions;
};

#endif // !LIBRARY_H
