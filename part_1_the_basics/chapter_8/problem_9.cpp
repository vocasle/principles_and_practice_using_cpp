// This file contains solution for exercise 9 of chapter 8

#include <vector>
#include <iostream>
#include <stdexcept>

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

auto compute_index(const std::vector<double>& price, const std::vector<double>& weight)
{
	if (price.size() != weight.size())
		error("price is not equal to weight");
	auto index = 0.0;
	for (size_t i = 0; i < price.size(); ++i)
		index += price.at(i) * weight.at(i);
	return index;
}

int main()
{
	auto price = {
		10.2,
		39.5,
		44.5,
		99.0
	};

	auto weight = {
		33.4,
		22.3,
		100.34,
		9.56
	};

	std::cout << "Index: " << compute_index(price, weight) << std::endl;
	return 0;
}