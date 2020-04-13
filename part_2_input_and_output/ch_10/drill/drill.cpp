// This file contains solution for drill’s step 1 and 2 of chapter 10 

#include "point.hpp"

#include <vector>
#include <iostream>

void prompt_for_input(const std::string& msg)
{
	std::cout << msg << std::endl;
}

void end_of_loop(std::istream& is, char term, const std::string& msg)
{
	if (is.fail())
	{
		is.clear();
		char ch;
		if (is >> ch && ch == term)
		{
			return;
		}
		error(msg);
	}
}

std::vector<Point> get_points()
{
	std::vector<Point> points;
	for (Point p; std::cin >> p;)
	{
		points.push_back(p);
	}
	end_of_loop(std::cin, ';', "Bad termination of input.");
	return points;
}

void print_points(const std::vector<Point>& points)
{
	for (auto& p : points)
	{
		std::cout << p << '\n';
	}
}

int main()
{
	std::cin.exceptions(std::cin.exceptions() | std::ios_base::badbit);
	prompt_for_input("Enter 7 points. To terminate the input enter semicolon (;).");
	prompt_for_input("Example: (2 5) (3 5);");
	try
	{
		std::vector<Point> original_points = get_points();
		print_points(original_points);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
}