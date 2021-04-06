#pragma once

#include <string>
#include <iostream>

#if WIN32
#include "Windows.h"
#endif

template <typename T>
void print_test_failed(const T& lhs, const T& rhs)
{
#if WIN32
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(console, &info);
	SetConsoleTextAttribute(console, FOREGROUND_RED);
#endif
	std::cout << "Test failed. " << lhs << " != " << rhs << std::endl;
#if WIN32
	SetConsoleTextAttribute(console, info.wAttributes);
#endif

}

/**
 * Prints "Test passes lhs == rhs" to stdout
 * @param lhs left hand side operand
 * @param rhs right hand side operand
 */
template <typename T>
void print_test_succeeded(const T& lhs, const T& rhs)
{
#if WIN32
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(console, &info);
	SetConsoleTextAttribute(console, FOREGROUND_GREEN);
#endif
	std::cout << "Test passed. " << lhs << " == " << rhs << std::endl;
#if WIN32
	SetConsoleTextAttribute(console, info.wAttributes);
#endif

}

/**
 * Tests whether lhs equals to rhs and prints result to stdout. It uses operator== for comparison.
 * @param lhs left hand side operand
 * @param rhs right hand side operand
 */
void test_equal(const std::string& lhs, const std::string& rhs)
{
	if (lhs != rhs)
	{
		print_test_failed(lhs, rhs);
	}
	else
	{
		print_test_succeeded(lhs, rhs);
	}
}

/**
 * Helper function to exit only after Enter key is pressed
 */
void exit_after_enter()
{
	puts("Press Enter to exit...");
	std::cin.get();
}

/**
 * Calculates length of the C-string
 * @param str C-string
 * @return number of characters in string
 */
uint32_t str_len(const char* str)
{
	uint32_t size = 0;
	while (str && *str)
	{
		++str;
		++size;
	}

	return size;
}