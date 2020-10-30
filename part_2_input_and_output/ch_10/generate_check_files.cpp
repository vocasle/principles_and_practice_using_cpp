#include "utility.hpp"
#include "generate_check_files.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>

static const std::map<uint32_t, std::string> numerals{
	{1, "I"},
	{2, "II"},
	{3, "III"},
	{4, "IV"},
	{5, "V"},
	{6, "VI"},
	{7, "VII"},
	{8, "VIII"},
	{9, "IX"},
	{10, "X"},
	{20, "XX"},
	{30, "XXX"},
	{40, "XL"},
	{50, "L"},
	{60, "LX"},
	{70, "LXX"},
	{80, "LXXX"},
	{90, "XC"},
	{100, "C"},
	{200, "CC"},
	{300, "CCC"},
	{400, "CD"},
	{500, "D"},
	{600, "DC"},
	{700, "DCC"},
	{800, "DCCC"},
	{900, "CM"},
	{1000, "M"},
	{2000, "MM"},
	{3000, "MMM"}
};

void generate_test_file(const std::string& file_name)
{
	std::ofstream ofs{ file_name };
	if (!ofs)
	{
		error("'" + file_name + "' could not be opened for writing.");
	}
	for (int i = 1; i < 4000; ++i)
	{
		ofs << num_to_roman(i) << ' ' << i << '\n';
	}
}

std::map<uint32_t, std::string> read_test_file(const std::string& file_name)
{
	std::ifstream ifs{ file_name };
	if (!ifs)
	{
		error("'" + file_name + "' could not be opened for reading.");
	}
	std::map<uint32_t, std::string> roman_nums;
	uint32_t val{ 0 };
	std::string rnum;
	while (ifs >> rnum >> val)
	{
		roman_nums[val] = rnum;
	}
	return roman_nums;
}


std::string val_to_rnum(uint32_t i)
{
	auto found = numerals.find(i);
	if (found == numerals.end())
	{
		error(std::to_string(i) + " is out of [1, 3999]");
	}
	return found->second;
}

std::string num_to_roman(uint32_t num)
{
	auto size = std::to_string(num).size();
	std::vector<uint32_t> nums;
	uint32_t prev{ 0 };
	for (int i = 0; i != size; ++i)
	{
		auto div = static_cast<uint32_t>(std::pow(10, (i + 1)));
		auto curr = num % div;
		nums.push_back(curr - prev);
		prev = curr;
	}
	std::reverse(nums.begin(), nums.end());
	std::ostringstream oss;
	for (auto& n : nums)
	{
		if (n != 0)
		{
			oss << val_to_rnum(n);
		}
	}
	return oss.str();
}