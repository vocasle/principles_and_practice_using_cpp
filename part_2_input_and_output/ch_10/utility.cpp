#include "utility.hpp"

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}