#include "point.hpp"

#include <stdexcept>

void error(const std::string& err_msg)
{
	throw std::runtime_error(err_msg);
}

std::istream& operator>>(std::istream& is, Point& p)
{
	char ch1;
	char ch2;
	uint32_t x{ 0 };
	uint32_t y{ 0 };
	is >> ch1;
	if (ch1 != '(')
	{
		is.unget();
		is.clear(std::ios_base::failbit);
		return is;
	}
	is >> x >> y;
	is >> ch2;
	if (ch2 != ')')
	{
		error("Point coordinates must end with ')'");
	}
	if (!is)
	{
		return is;
	}
	p.x = x;
	p.y = y;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << '(' << p.x << ' ' << p.y << ')';
	return os;
}

bool operator==(const Point& lhs, const Point& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Point& lhs, const Point& rhs)
{
	return !(lhs == rhs);
}