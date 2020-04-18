#include "roman_int.hpp"
#include "utility.hpp"

#include <iostream>
#include <sstream>

uint32_t get_M(std::istream& is)
{
	uint32_t num{ 0 };
	char ch;
	uint32_t repeats{ 0 };
	while (repeats < Roman_int::max_repeating_numerals && is >> ch)
	{
		if (ch == 'M')
		{
			num += 1000;
		}
		else
		{
			is.unget();
			break;
		}
		++repeats;
	}
	return num;
}

uint32_t get_C(std::istream& is)
{
	uint32_t num{ 0 };
	char ch;
	uint32_t repeats{ 0 };
	while (repeats < Roman_int::max_repeating_numerals && is >> ch)
	{
		switch (ch)
		{
		case 'M':
		{
			if (repeats == 1)
			{
				return num + 800;
			}
			else
			{
				error("Invalid roman numeral.");
			}
		}
		case 'D':
		{
			if (repeats > 0)
			{
				return num + 300;
			}
			else
			{
				num += 500;
			}
			break;
		}
		case 'C':
		{
			num += 100;
			++repeats;
			break;
		}
		default:
			is.unget();
			return num;
		}
	}
	return num;
}

uint32_t get_X(std::istream& is)
{
	uint32_t num{ 0 };
	char ch;
	uint32_t repeats{ 0 };
	while (repeats < Roman_int::max_repeating_numerals && is >> ch)
	{
		switch (ch)
		{
		case 'C':
		{
			if (repeats == 1)
			{
				return num + 80;
			}
			else
			{
				error("Invalid roman numeral.");
			}
		}
		case 'L':
		{
			if (repeats > 0)
			{
				return num + 30;
			}
			else
			{
				num += 50;
			}
			break;
		}
		case 'X':
		{
			num += 10;
			++repeats;
			break;
		}
		default:
			is.unget();
			return num;
		}
	}
	return num;
}

uint32_t get_I(std::istream& is)
{
	uint32_t num{ 0 };
	char ch;
	uint32_t repeats{ 0 };
	while (repeats < Roman_int::max_repeating_numerals && is >> ch)
	{
		switch (ch)
		{
		case 'X':
			return num + 8;
		case 'V':
		{
			if (repeats > 0)
			{
				return num + 3;
			}
			else
			{
				num += 5;
			}
			break;
		}
		case 'I':
		{
			num += 1;
			++repeats;
			break;
		}
		default:
			error("Invalid roman numeral.");
		}
	}
	return num;
}

uint32_t Roman_int::as_int() const
{
	std::stringstream ss{ m_numerals };
	auto n = get_M(ss) + get_C(ss) + get_X(ss) + get_I(ss);
	std::string left;
	std::getline(ss, left);
	if (!left.empty())
	{
		error("Invalid roman numeral.");
	}
	return n;
}

Roman_int::Roman_int(const std::string& numerals): m_numerals{numerals}
{
	if (numerals.empty())
	{
		error("Empty string is not a valid input.");
	}
}