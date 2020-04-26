// This program converts hexadecimal, octal and decimal integers to
// decimal

#include "chapter_11.hpp"

#include <iomanip>
#include <sstream>
#include <regex>

enum class NumberSystem
{
	hex,dec,oct
};

std::string ns_to_str(NumberSystem ns)
{
	switch (ns)
	{
	case NumberSystem::hex:
		return "hexadecimal";
	case NumberSystem::dec:
		return "decimal";
	case NumberSystem::oct:
		return "octal";
	}
}

void unset_stream(std::istream&);

void print_number(const std::string& number, NumberSystem ns)
{
	std::istringstream iss{ number };
	unset_stream(iss);
	int num{ 0 };
	iss >> num;
	std::cout << std::setw(10)
		<< number << ' ' + ns_to_str(ns)
		<< "\tconverts to "
		<< std::setw(10)
		<< num << "\tdecimal\n";
}

NumberSystem get_ns(const std::string& num)
{
	std::regex hex_rx{ "0x(([A-F])+|\\d)+" };
	std::regex oct_rx{ "0[01234567]+" };
	std::regex dec_rx{ "\\d+" };
	if (std::regex_match(num, hex_rx))
	{
		return NumberSystem::hex;
	}
	else if (std::regex_match(num, oct_rx))
	{
		return NumberSystem::oct;
	}
	else if (std::regex_match(num, dec_rx) && !(num.at(0) == '0' && num.size() > 1))
	{
		return NumberSystem::dec;
	}
	else
	{
		error(num + " is not a valid integer.");
	}
}

void read_numbers()
{
	std::cout << "Enter several integers in any combination of octal, hexadecimal"
		<< " or decimal, using 0 and 0x suffixes:\n";
	std::string number;
	while (std::cin >> number)
	{
		print_number(number, get_ns(number));
	}

	if (!std::cin)
	{
		std::cin.clear();
		std::string line;
		std::getline(std::cin, line);
		error(line + " is not an integer.");
	}
}

void unset_stream(std::istream& is)
{
	is.unsetf(std::ios::dec);
	is.unsetf(std::ios::hex);
	is.unsetf(std::ios::oct);
}

int main()
{
	unset_stream(std::cin);
	try
	{
		read_numbers();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}