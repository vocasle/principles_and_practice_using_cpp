// This file contains solution for exercise 13 of chapter 8

#include "chapter_8.h"

std::vector<size_t> str_lengths(const std::vector<std::string>& strings)
{
	std::vector<size_t> lengths;
	for (const auto& str : strings)
		lengths.push_back(str.size());
	return lengths;
}

struct StringData
{
	std::string longest;
	std::string shortest;
	std::string first;
	std::string last;
};

void find_longest_and_shortest_str(const std::vector<std::string>& strings, StringData& sd)
{
	auto it = strings.begin();
	auto longest = *it;
	auto shortest = *it;
	for (it = it + 1; it < strings.end(); ++it)
	{
		if (longest.size() < it->size())
			longest = *it;
		if (shortest.size() > it->size())
			shortest = *it;
	}
	sd.longest = longest;
	sd.shortest = shortest;
}

void find_first_and_last_str(const std::vector<std::string>& strings, StringData& sd)
{
	auto min_max = std::minmax_element(strings.begin(), strings.end());
	sd.first = *min_max.first;
	sd.last = *min_max.second;
}

StringData analyze_strings(const std::vector<std::string>& strings)
{
	if (strings.size() == 0)
		error("empty vector of strings");
	StringData sd;
	find_first_and_last_str(strings, sd);
	find_longest_and_shortest_str(strings, sd);
	return sd;
}

int main()
{
	try
	{
		std::vector<std::string> strings{
			"When", "you", "have", "exhausted", "all", "posibilities", ",", "remember",
			"this", "-", "you", "haven't", "."
		};

		auto lengths = str_lengths(strings);
		auto sd = analyze_strings(strings);

		std::cout << "Longest: '" << sd.longest
			<< "'\nShortest: '" << sd.shortest
			<< "'\nLexicographically first: '" << sd.first
			<< "'\nLexicographically last: '" << sd.last
			<< "'\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}