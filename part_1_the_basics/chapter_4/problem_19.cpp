//
// Created by Nikita Elsakov on 12.03.2020.
//

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

int main()
{
	std::cout << "Enter name followed by score, e.g. 'Ann 20'.\n"
			  << "To terminate input enter 'NoName 0'.\n";
	std::vector<std::string> names;
	std::vector<int32_t> scores;

	std::string name = "";
	int32_t score = 0;
	for (; std::cin >> name >> score;)
	{
		if (name == "NoName" && score == 0)
			break;
		if (std::find(names.begin(), names.end(), name) != names.end())
			throw std::runtime_error(std::string("'" + name + "' is a duplicate name."));
		names.push_back(name);
		scores.push_back(score);
	}

	std::cout << "Enter the name for which you want to find a score or enter"
			  << " a score for which you want to find a name:\n";
	std::cin >> name;
	try
	{
		score = std::stoi(name);
		auto it = std::find(scores.begin(), scores.end(), score);
		if (it == scores.end())
			std::cerr << "'" << score << "' not found.\n";
		else
			std::cout << "Name for score " << score << " is: " << names.at(it - scores.begin()) << '\n';
	}
	catch (std::invalid_argument& e)
	{
		auto it = std::find(names.begin(), names.end(), name);
		if (it == names.end())
			std::cerr << "'" << name << "' not found.\n";
		else
			std::cout << "Score for " << name << " is: " << scores.at(it - names.begin()) << '\n';
	}
	return 0;
}

