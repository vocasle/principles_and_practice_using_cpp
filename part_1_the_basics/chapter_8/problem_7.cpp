// This file contains solutions for exercise 7 of chapter 8

#include "problem_7.h"

int main()
{
	auto names = get_names(std::cin);
	auto ages = get_ages(names, std::cin);
	print("unames", names);
	print("uages", ages);
	sort_names_and_ages(names, ages);
	print("snames", names);
	print("sages", ages);
	return 0;
}