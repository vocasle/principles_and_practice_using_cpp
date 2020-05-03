#include <vector>
#include <string>
#include <iostream>


void print_vector(const std::vector<std::string>& vec, const std::string& del)
{
	for (auto& el : vec)
	{
		std::cout << el << del;
	}
}

// splits string str into vector of strings
std::vector<std::string> split(const std::string& str, const std::string& delim)
{
	auto word = std::string{};
	auto words = std::vector<std::string>{};
	auto offset = 0u;
	auto pos = 0u;
	for (auto pos = str.find(delim, offset); pos != std::string::npos;)
	{
		auto substr = str.substr(offset, pos - offset);
		words.push_back(substr);
		offset = pos + 1;
		pos = str.find(delim, offset);
	}
	words.push_back(str.substr(offset, pos - offset));
	return words;
}

int main()
{
	print_vector(split("This is a test string.\nThis is second string.", "\n"), "\n");
}