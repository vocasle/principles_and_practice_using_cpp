#include <string>

#include "helper_functions.h"


#include <iostream>

/**
 * Reverses the string
 * @param s string to reverse
 * @return reversed string
 */
std::string reverse(const std::string& s)
{
	std::string rev(s.size(), '\0');
	int end = s.size() - 1;
	for (int cnt = end; cnt >= 0; --cnt)
	{
		rev[end - cnt] = s[cnt];
	}
	return rev;
}

/**
 * Reverses the string
 * @param in C-string to reverse
 * @param size number of characters in C-string
 * @return reversed heap allocated C-string
 */
char* reverse(const char* in, int size)
{
	if (!in)
	{
		return nullptr;
	}
	int last = size - 1;
	char* buffer = new char[size + 1];
	for (int i = 0; i < size + 1; i++)
	{
		*(buffer + i) = 0;
	}
	while (*in)
	{
		*(buffer + last--) = *in++;
	}
	*(buffer + size) = '\0';
	return buffer;
}

/**
 * Determines whether string is a palindrome
 * @param s string to test if it is a palindrome
 * @return true if s is a palindrome, false otherwise
 */
bool is_palindrome(const std::string& s)
{
	const std::string reversed = reverse(s.c_str());
	return s == reversed;
}

/**
 * Compares two C-strings
 * @param lhs C-string
 * @param rhs C-string
 * @return true if strings are equal, false otherwise
 */
bool str_comp(const char* lhs, const char* rhs)
{
	while (lhs && rhs && *lhs && *rhs)
	{
		if (*lhs++ != *rhs++)
		{
			return false;
		}
	}
	return true;
}

/**
 * Determines whether string is a palindrome
 * @param s string to test if it is a palindrome
 * @param n number of characters in C-string
 * @return true if s is a palindrome, false otherwise
 */
bool is_palindrome(const char s[], int n)
{
	char* rev = reverse(s, n);
	bool isPalindrome = str_comp(rev, s);
	delete[] rev;
	return isPalindrome;
}

/**
 * Determines whether string is a palindrome
 * @param first pointer to the first character of C-string to test if it is a palindrome
 * @param last pointer to the last character of C-string
 * @return true if C-string is a palindrome, false otherwise
 */
bool is_palindrome(const char* first, const char* last)
{
	const char* rev = reverse(first, str_len(first));
	bool isPalindrome = str_comp(rev, first);
	delete[] rev;
	return isPalindrome;
}


void main()
{
	const char* str = "OTTO";
	const char* str2 = "Otto";
	std::cout << "James is " << (is_palindrome("James") ? "a palindrome" : "not a palindrome")
		<< "\nOTTO is " << (is_palindrome(str, str_len(str)) ? "a palindrome" : "not a palindrome")
		<< "\nOtto is "  <<  (is_palindrome(str2, (str2 + str_len(str2) - 1)) ? "a palindrome" : "not a palindrome")
		<< std::endl;
	exit_after_enter();
}