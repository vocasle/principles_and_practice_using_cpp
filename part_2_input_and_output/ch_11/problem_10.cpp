// This file contains solution for exercise 10 and 11 of chapter 11

#include <vector>
#include <string>
#include <iostream>

#include "chapter_11.hpp"

void print_vector(const std::vector<std::string>& vec, const std::string& del)
{
	for (auto& el : vec)
	{
		std::cout << el << del;
	}
}

int main()
{
	print_vector(split("This is a test string.\nThis is second string.", "\n"), "\n");
}
