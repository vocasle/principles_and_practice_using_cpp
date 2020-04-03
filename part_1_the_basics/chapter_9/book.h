// This file contains Book class' declaration
// Rev 1: Solution for ex. 5 of chapter 9
// Rev 2: Solution for ex. 6 of chapter 9

#include <string>
#include <iostream>
#include "date.h"

class Book
{
public:
	Book(
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
	std::string isbn;
	std::string title;
	std::string author;
	Date copyright_date;
	bool is_chkd_out;
};

std::ostream& operator<<(std::ostream& os, const Book& book);
bool operator==(const Book& lhs, const Book& rhs);
bool operator!=(const Book& lhs, const Book& rhs);