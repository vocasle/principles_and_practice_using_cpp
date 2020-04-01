#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

template <typename T>
void print(const std::string& label, const std::vector<T>& vec)
{
	for (auto&& el : vec)
		std::cout << label << ' ' << el << '\n';
}