// This file contains solution for exercise 12 of chater 8
//
// A good test case in my humble opinion should contain:
// firstly: expected inputs
// secondly: unexpected inputs that will compile
// 

#include "chapter_8.h"

void print_until_s(const std::vector<std::string>& v, const std::string& quit)
{
	for (auto&& s : v)
	{
		if (s == quit)
			return;
		std::cout << s << '\n';
	}
}

void print_until_ss(const std::vector<std::string>& v, const std::string& quit)
{
	auto cnt = 0;
	for (auto&& s : v)
	{
		if (s == quit)
		{
			++cnt;
			if (cnt > 1)
				return;
		}
		std::cout << s << '\n';
	}
}

int main()
{
	std::vector<std::string> strings{
		"When", "you", "have", "exhausted", "all", "posibilities", ",", "remember",
		"this", "-", "you", "haven't", "."
	};

	//print_until_s(strings, "When");
	//print_until_s(strings, "\0");
	//print_until_s(strings, "hello");
	//print_until_s(strings, "-");
	
	//print_until_ss(strings, "When");
	//print_until_ss(strings, "\0");
	//print_until_ss(strings, "hello");
	//print_until_ss(strings, "-");
	//print_until_ss(strings, "you");

	return 0;
}