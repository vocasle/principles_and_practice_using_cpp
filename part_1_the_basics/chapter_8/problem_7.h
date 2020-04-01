#include "chapter_8.h"
#include <algorithm>



std::vector<std::string> get_names(std::istream& is)
{
	std::cout << "Enter names separated by space character and press enter:\n";
	std::vector<std::string> names;
	std::string line;
	std::getline(is, line);
	std::string name;
	size_t next = 0;
	size_t last = 0;
	char delimiter = ' ';
	while ((next = line.find(delimiter, last)) != std::string::npos)
	{
		auto subs = line.substr(last, next - last);
		names.push_back(subs);
		last = next + 1;
	}
	names.push_back(line.substr(last, next - last)); // handle last name
	return names;
}

std::vector<int32_t> get_ages(const std::vector<std::string>& names, std::istream& is)
{
	std::vector<int32_t> ages;
	auto age = 0;
	for (auto&& name : names)
	{
		std::cout << "Enter " << name << "'s age: ";
		is >> age;
		ages.push_back(age);
	}
	return ages;
}

void sort_names(std::vector<std::string>& names)
{
	std::sort(names.begin(), names.end());
}

void sort_names_and_ages(std::vector<std::string>& names, std::vector<int32_t>& ages)
{
	std::vector<std::string> unsorted_names(names);
	std::vector<int32_t> unsorted_ages(ages);
	sort_names(names);
	for (auto it = names.begin(); it != names.end(); ++it)
	{
		auto found = std::find(unsorted_names.begin(), unsorted_names.end(), *it);
		if (found == unsorted_names.end())
			error(*it + " not found");
		auto found_pos = found - unsorted_names.begin();
		auto cur_pos = it - names.begin();
		ages[cur_pos] = unsorted_ages[found_pos];
	}
}
