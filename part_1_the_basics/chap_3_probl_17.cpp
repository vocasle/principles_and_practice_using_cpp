//
// Created by Nikita Elsakov on 09.03.2020.
//
// This program finds mode, minimum and maximum (lexicographically) in set of strings
//

#include "chap_3_probl_16.h"
#include <string>

int main()
{
	std::cout << "Enter strings separated by space.\n"
			  << "To terminate input enter '.' character and press enter:\n";

	std::vector<std::string> strings;
	for (std::string s = ""; std::cin >> s;)
	{
		if (s == ".")
			break;
		strings.push_back(s);
	}
	if (strings.empty())
		return 0;

	std::string min = strings.at(0);
	std::string max = min;
	for (auto it = strings.begin() + 1; it != strings.end(); ++it)
	{
		if (max < *it)
			max = *it;
		if (min > *it)
			min = *it;
	}
	std::cout << "Minimum: " << min
			  << "\nMaximum: " << max
			  << "\nMode: " << findMode(strings) << std::endl;
	return 0;
}

