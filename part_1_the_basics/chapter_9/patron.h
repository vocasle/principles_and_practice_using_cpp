// This file contains declaration of Patron class
// Rev 1:
// - Declaration of Patron class
// - Declaration of owes_fees helper function
//

#include <string>

class Patron
{
public:
	Patron(const std::string& name, const std::string& card_number, double fees);
	std::string get_name() const;
	std::string get_card_number() const;
	double get_fees() const;
	void set_fees(double new_fee);
private:
	std::string name;
	std::string card_number;
	double fees;
};

bool owes_fees(const Patron& patron);