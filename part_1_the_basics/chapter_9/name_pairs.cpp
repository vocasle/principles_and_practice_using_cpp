#include "name_pairs.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

void Name_pairs::read_names()
{
	std::cout << "Enter list of names delimited with comma:\n";
	static const std::string delimeter = ",";
	std::string input;
	std::getline(std::cin, input);
	size_t pos = 0;
	while ((pos = input.find(delimeter)) != std::string::npos)
	{
		name.push_back(trim(input.substr(0, pos)));
		input.erase(0, pos + 1);
	}
	// handle cases when there is one more name after delimiter
	if (!input.empty())
		name.push_back(trim(input));
}

void Name_pairs::read_ages()
{
	for (const auto& n : name)
	{
		double a{ 0 };
		while (std::cout << "Enter " << n << "'s age: " &&
			(!(std::cin >> a) || a <= 0))
		{
			std::cin.clear();
			std::string line;
			std::getline(std::cin, line);
			std::cerr << "'" << line << "' is not a correct age\n";
		}
		age.push_back(a);
	}
}

void Name_pairs::print()
{
	for (size_t i = 0; i < name.size(); ++i)
		std::cout << name.at(i) << ", " << age.at(i) << '\n';
}

void Name_pairs::sort()
{
	auto name_orig{ name };
	std::vector<double> sorted_age(age.size());
	std::vector<size_t> processed_indexes;
	std::sort(name.begin(), name.end());
	for (size_t i = 0; i < name.size(); ++i)
	{
		auto pos = std::find(name_orig.begin(), name_orig.end(), name.at(i)) - name_orig.begin();
		while (std::find(processed_indexes.begin(), processed_indexes.end(), pos) != processed_indexes.end())
			pos = std::find(name_orig.begin() + pos + 1, name_orig.end(), name.at(i)) - name_orig.begin();
		sorted_age[i] = age.at(pos);
		processed_indexes.push_back(pos);
	}
	age = sorted_age;
}

std::string trim(const std::string& s)
{
	std::stringstream ss;
	for (const auto& c : s)
		if (c != ' ')
			ss << c;
	return ss.str();
}

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}