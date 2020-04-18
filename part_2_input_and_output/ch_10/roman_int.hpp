#ifndef ROMAN_INT_HPP
#define ROMAN_INT_HPP
#include <string>

class Roman_int
{
public:
	Roman_int(const std::string& numerals);
	static const uint32_t max_repeating_numerals = 3;
	uint32_t as_int() const;
private:
	std::string m_numerals;
};
#endif // !ROMAN_INT_HPP
