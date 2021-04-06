#include <string>
#include <iostream>

#include "helper_functions.h"

/**
 * Exercise 5 solution
 * Joins two strings with dot in between
 * @param s1	first string
 * @param s2	second string
 * @return concatenated string
 */
std::string cat_dot(const std::string& s1, const std::string& s2)
{
	return s1 + "." + s2;
}

/**
 * Exercise 6 solution
 * Joins three strings together with delim between s1 and s2
 * @param s1	first string
 * @param s2	second string
 * @param delim delimiter
 * @return concatenated string
 */
std::string cat_dot(const std::string& s1, const std::string& s2, const std::string& delim)
{
	return s1 + s2 + delim;
}

int main()
{
	test_equal("John.Doe", cat_dot("John", "Doe"));
	test_equal("John Joseph Doe", cat_dot("John", "Joseph", "Doe"));
	exit_after_enter();
}
