#include <vector>
#include <string>
#include <iostream>

void print(const std::string& label, const std::vector<int>& numbers)
{
	for (auto&& number : numbers)
		std::cout << label << ' ' << number << '\n';
}