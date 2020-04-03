// This file contains Book class' definition
// Rev 1: Solution for ex. 5 of chapter 9

#include "book.h"
#include <regex>

Book::Book(
	const std::string& isbn,
	const std::string& title,
	const std::string& author,
	const Date& copyright_date,
	bool is_checked_out
) : isbn{ isbn },
title{ title },
author{ author },
copyright_date{ copyright_date },
is_chkd_out{ is_checked_out }
{
	std::regex regex{ R"(\d+-\d+-\d+-(\w|\d+))" };
	if (!std::regex_match(isbn, regex))
		error("'" + isbn + "' is not a correct ISBN.");
}

std::string Book::get_author() const
{
	return author;
}

Date Book::get_copyright_date() const
{
	return copyright_date;
}

std::string Book::get_isbn() const
{
	return isbn;
}

std::string Book::get_title() const
{
	return title;
}

bool Book::is_checked_out() const
{
	return is_chkd_out;
}

void Book::check_in()
{
	is_chkd_out = false;
}

void Book::check_out()
{
	is_chkd_out = true;
}