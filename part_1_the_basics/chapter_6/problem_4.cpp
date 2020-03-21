//
// Created by Nikita Elsakov on 21.03.2020.
//
// Updated solution for exercise 19 of chapter 4 as a solution
// for problem 4 of chapter 6

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <stdexcept>

class NameValue
{
public:
	NameValue(std::string name, int32_t value) : name(std::move(name)), value(value)
	{
	}
	std::string name;
	int32_t value;
};

int main()
{
	std::cout << "Enter name followed by score, e.g. 'Ann 20'.\n"
			  << "To terminate input enter 'NoName 0'.\n";
	std::vector<NameValue> nameValues;

	std::string name{};
	int32_t score = 0;
	auto findNameValueByName = [&](const auto& nameValue) -> bool
	{
	  return nameValue.name == name;
	};
	auto findNameValueByScore = [&](const auto& nameValue) -> bool
	{
	  return nameValue.value == score;
	};
	for (; std::cin >> name >> score;)
	{
		if (name == "NoName" && score == 0)
			break;
		if (std::find_if(nameValues.begin(), nameValues.end(), findNameValueByName) != nameValues.end())
			throw std::runtime_error(std::string("'" + name + "' is a duplicate name."));
		nameValues.emplace_back(name, score);
	}

	std::cout << "Enter the name for which you want to find a score or enter"
			  << " a score for which you want to find a name:\n";
	std::cin >> name;
	try
	{
		score = std::stoi(name);
		auto it = std::find_if(nameValues.begin(), nameValues.end(), findNameValueByScore);
		if (it == nameValues.end())
			std::cerr << "'" << score << "' not found.\n";
		else
			std::cout << "Name for score " << score << " is: " << nameValues.at(it - nameValues.begin()).name << '\n';
	}
	catch (std::invalid_argument& e)
	{
		auto it = std::find_if(nameValues.begin(), nameValues.end(), findNameValueByName);
		if (it == nameValues.end())
			std::cerr << "'" << name << "' not found.\n";
		else
			std::cout << "Score for " << name << " is: " << nameValues.at(it - nameValues.begin()).value << '\n';
	}
	return 0;
}

