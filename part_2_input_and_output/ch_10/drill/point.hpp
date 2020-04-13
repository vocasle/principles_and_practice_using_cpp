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
void error(const std::string& err_msg);
#endif // !POINT_HPP
