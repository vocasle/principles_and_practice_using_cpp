// This file contains definitions of Patron class methods and helper functions
// Rev 1:
// - Definition of Patron class' methods
// - Definitions of owes_fees helper function
//

#include "patron.h"

Patron::Patron(const std::string& name, const std::string& card_number, double fees)
	: name{ name }, card_number{ card_number }, fees{ fees }
{

}

std::string Patron::get_card_number() const
{
	return card_number;
}

std::string Patron::get_name() const
{
	return name;
}

double Patron::get_fees() const
{
	return fees;
}

void Patron::set_fees(double new_fees)
{
	fees = new_fees;
}

// ------------------------------------------------
// helper functions
// ------------------------------------------------

bool owes_fees(const Patron& patron)
{
	return !(patron.get_fees() < 0.001);
}

bool operator==(const Patron& lhs, const Patron& rhs)
{
	return lhs.get_card_number() == rhs.get_card_number();
}