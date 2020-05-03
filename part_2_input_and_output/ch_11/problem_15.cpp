#include "chapter_11.hpp"

#include <fstream>
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

void write_numbers(const std::vector<double>& nums, const std::string& fname)
{
	auto file = std::ofstream{ fname };
	if (!file)
	{
		file_open_err(fname, FileType::out);
	}
	file << std::scientific << std::setprecision(8);
	auto prnt_cnt = 0u;
	for (auto& num : nums)
	{
		++prnt_cnt;
		file << std::setw(5) << num << '\t';
		if (prnt_cnt == 4)
		{
			prnt_cnt = 0;
			file << '\n';
		}
	}
	if (file.bad() || file.fail())
	{
		error("Failed to write data to the file " + fname);
	}
}

int main()
{
	try
	{
		auto in = prompt_filename(FileType::in);
		auto numbers = read_numbers(in);
		auto out = prompt_filename(FileType::out);
		write_numbers(numbers, out);
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