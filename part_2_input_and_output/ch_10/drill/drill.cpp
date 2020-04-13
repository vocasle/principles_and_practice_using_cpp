// This file contains solution for drill’s step 1 and 2 of chapter 10 

#include "point.hpp"

#include <vector>
#include <iostream>
#include <fstream>

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
		if (is >> ch && ch == term || is.eof())
		{
			return;
		}
		error(msg);
	}
}

std::vector<Point> get_points(std::istream& is)
{
	std::vector<Point> points;
	for (Point p; is >> p;)
	{
		points.push_back(p);
	}
	end_of_loop(is, ';', "Bad termination of input.");
	return points;
}

void print_points(const std::vector<Point>& points)
{
	for (auto& p : points)
	{
		std::cout << p << '\n';
	}
}

void write_points_to_file(const std::string& file_name, const std::vector<Point>& points)
{
	std::ofstream ofs{ file_name };
	if (!ofs)
	{
		error("Could not open file '" + file_name + "' for writing.");
	}
	for (auto& p : points)
	{
		ofs << p << '\n';
	}
}

std::vector<Point> read_points_from_file(const std::string& file_name)
{
	std::ifstream ifs{ file_name };
	if (!ifs)
	{
		error("Could not open file '" + file_name + "' for reading.");
	}
	return get_points(ifs);
}

bool are_set_equals(const std::vector<Point>& lhs, const std::vector<Point>& rhs)
{
	return  lhs.size() == rhs.size() && lhs == rhs;
}

int main()
{
	std::cin.exceptions(std::cin.exceptions() | std::ios_base::badbit);
	prompt_for_input("Enter 7 points. To terminate the input enter semicolon (;).");
	prompt_for_input("Example: (2 5) (3 5);");
	try
	{
		std::vector<Point> original_points = get_points(std::cin);
		print_points(original_points);
		write_points_to_file("mydata.txt", original_points);
		auto processed_points = read_points_from_file("mydata.txt");
		print_points(processed_points);
		if (!are_set_equals(original_points, processed_points))
		{
			std::cerr << "Something's wrong!\n";
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
}