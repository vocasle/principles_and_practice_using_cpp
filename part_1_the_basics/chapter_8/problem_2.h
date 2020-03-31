#include <vector>
#include <string>
#include <iostream>

template <typename T>
void print(const std::string& label, const std::vector<T>& numbers)
{
	for (auto&& number : numbers)
		std::cout << label << ' ' << number << '\n';
}