#include "chapter_11.hpp"

#include <fstream>
#include <algorithm>
#include <iomanip>

std::vector<double> read_numbers(const std::string& fname)
{
	auto file = std::ifstream{ fname };
	if (!file)
	{
		file_open_err(fname, FileType::in);
	}
	auto numbers = std::vector<double>();
	for (auto num = 0.0; file >> num;)
	{
		numbers.push_back(num);
	}
	if ((file.bad() || file.fail()) && !file.eof())
	{
		error("Failed to read data from file " + fname);
	}
	return numbers;
}

struct Pair
{
	double num;
	uint32_t cnt;
	Pair(double num, uint32_t cnt) : num{ num }, cnt{cnt} {}
};

void print_numbers(std::vector<double>& nums)
{
	auto prev = 123456789.987654321;
	auto cnt = 0u;
	auto occurences = std::vector<Pair>();
	std::sort(nums.begin(), nums.end());
	
	for (auto& num : nums)
	{
		if (num != prev)
		{
			occurences.emplace_back(prev, cnt);
			prev = num;
			cnt = 0;
		}
		else
		{
			++cnt;
		}
	}

	for (auto& pair : occurences)
	{
		std::cout << std::setw(8) << pair.num << '\t' << pair.cnt << '\n';
	}
}

int main()
{
	try
	{
		auto in = prompt_filename(FileType::in);
		auto numbers = read_numbers(in);
		print_numbers(numbers);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}
	catch (...)
	{
		std::cerr << "Unknown exception occured.\n";
		return -2;
	}
}