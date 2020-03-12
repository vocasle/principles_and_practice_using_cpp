//
// Created by Nikita Elsakov on 12.03.2020.
//

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

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

	for (auto i = 0; i < names.size(); ++i)
		std::cout << names.at(i) << ' ' << scores.at(i) << '\n';
	return 0;
}

