// This file contains Book class' declaration
// Rev 1: Solution for ex. 5 of chapter 9:
// - Define class Book
//
// Rev 2: Solution for ex. 6 of chapter 9:
// - Overload ==, !=, << operators for Book class
//
// Rev 3: Solution for ex. 7 of chapter 9:
// - Define Genre enum class
// - Add genre member to Book class
//
// Rev 4: Guard with #ifndef directive

#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include "date.h"

enum class Genre
{
	fiction, nonfiction, periodical, biography, children
};

class Book
{
public:
	Book(
		Genre genre,
		const std::string& isbn,
		const std::string& title,
		const std::string& author,
		const Date& copyright_date,
		bool is_checked_out
	);
	std::string get_isbn() const;
	std::string get_title() const;
	std::string get_author() const;
	Date get_copyright_date() const;
	bool is_checked_out() const;
	void check_out();
	void check_in();
private:
	Genre genre;
	std::string isbn;
	std::string title;
	std::string author;
	Date copyright_date;
	bool is_chkd_out;
};

std::ostream& operator<<(std::ostream& os, const Book& book);
bool operator==(const Book& lhs, const Book& rhs);
bool operator!=(const Book& lhs, const Book& rhs);

#endif // !BOOK_H
