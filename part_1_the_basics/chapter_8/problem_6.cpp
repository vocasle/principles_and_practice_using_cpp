// This file contains solution for exercise 6 of chapter 8

#include "problem_5.h"
#include "problem_2.h"
#include <string>

int main()
{
	std::vector<std::string> strings = {
		"Mercury",
		"Venus",
		"Earth",
		"Mars",
		"Jupiter",
		"Saturn",
		"Uranus",
		"Neptune"
	};

	const auto& cstrings = strings;
	auto reversed_strings = reverse(cstrings);
	print("reversed", reversed_strings);
	print("original", strings);
	reverse(strings);
	print("reversed", strings);
	print("original", strings);

	return 0;
}