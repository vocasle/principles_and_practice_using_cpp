#include <cinttypes>

#include "helper_functions.h"

/**
 * Exercise 7 solution
 * Joins two strings with dot in between
 * @param s1 first string
 * @param s2 second string
 * @return concatenated string
 */
char* cat_dot(const char* s1, const char* s2)
{
	uint32_t size = str_len(s1) + str_len(s2) + 2;
	char* str = new char[size];
	char* begin = str;
	uint32_t cnt = 0;
	while (s1 && *s1)
	{
		*str++ = *s1++;
	}
	*str++ = '.';
	while (s2 && *s2)
	{
		*str++ = *s2++;
	}
	*str = '\0';
	return begin;
}

/**
 * Exercise 7 solution
 * Joins three strings together with delim between s1 and s2
 * @param s1	first string
 * @param s2	second string
 * @param delim delimiter
 * @return concatenated string
 */
char* cat_dot(const char* s1, const char* s2, const char* delim)
{
	uint32_t size = str_len(s1) + str_len(s2) + str_len(delim) + 1;
	char* str = new char[size];
	char* begin = str;
	uint32_t cnt = 0;
	while (s1 && *s1)
	{
		*str++ = *s1++;
	}

	while (delim && *delim)
	{
		*str++ = *delim++;
	}

	while (s2 && *s2)
	{
		*str++ = *s2++;
	}
	*str = '\0';
	return begin;
}

int  main()
{
	const char* str = cat_dot("John", "Doe");
	const char* str2 = cat_dot("John", "Doe", " Abraham ");
	test_equal("John.Doe", str);
	test_equal("John Abraham Doe", str2);
	delete str;
	delete str2;
	exit_after_enter();
}
// END Ex 7
