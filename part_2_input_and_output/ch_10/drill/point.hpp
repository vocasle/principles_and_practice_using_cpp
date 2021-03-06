#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
#include <string>

struct Point
{
	int32_t x;
	int32_t y;
};

std::istream& operator>>(std::istream& is, Point& p);
std::ostream& operator<<(std::ostream& os, const Point& p);
bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);
void error(const std::string& err_msg);
#endif // !POINT_HPP
