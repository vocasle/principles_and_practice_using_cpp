#include "chapter_11.hpp"

#include <fstream>

void reverse_strings(const std::string& from, const std::string& to)
{
	std::ifstream in_file{ from };
	if (!in_file)
	{
		file_open_err(from, FileType::in);
	}
	std::ofstream out_file{ to };
	if (!out_file)
	{
		file_open_err(to, FileType::out);
	}
	in_file.exceptions(in_file.exceptions() | std::ios::badbit);
	out_file.exceptions(out_file.exceptions() | std::ios::badbit);
	auto strings = std::vector<std::string>();
	for (auto line = std::string(); std::getline(in_file, line);)
	{
		auto words = split(line);
		std::reverse(words.begin(), words.end());
		strings.insert(strings.begin(), words.begin(), words.end());
		strings.push_back("\n");
	}
	if (in_file.fail() && !in_file.eof())
	{
		error("An error occurred while reading data from file '" + from + "'.");
	}

	for (auto& str : strings)
	{
		out_file << str << ' ';
	}
	if (out_file.fail())
	{
		error("An error occurred while writing data to file '" + to + "'.");
	}
}

int main()
{
	try
	{
		auto from = prompt_filename(FileType::in);
		auto to = prompt_filename(FileType::out);
		reverse_strings(from, to);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}