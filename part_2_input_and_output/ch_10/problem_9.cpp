#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include "utility.hpp"

std::vector<std::string> split_str(const std::string& str, char sep)
{
	std::vector<std::string> strings;
	if (str.empty())
	{
		return strings;
	}
	size_t pos = str.find(sep);
	size_t offset{ 0 };
	while (pos != std::string::npos)
	{
		auto substr = str.substr(offset, pos - offset);
		strings.push_back(substr);
		offset = offset + (pos - offset) + 1;
		pos = str.find(sep, offset);
	}
	// deal with the last token after sep
	strings.push_back(str.substr(offset, pos - offset));
	return strings;
}

std::vector<std::string> get_words(std::istream& is)
{
	std::vector<std::string> words;
	std::string line;
	while (std::getline(is, line))
	{
		auto split_line = split_str(line, ' ');
		words.insert(words.end(), split_line.begin(), split_line.end());
	}
	return words;
}

void write_sorted_words(const std::string& file_name, 
	const std::vector<std::string>& words)
{
	std::ofstream out_file{ file_name };
	if (!out_file)
	{
		error("Could not open '" + file_name + "' for writing.");
	}
	for (auto& word : words)
	{
		out_file << word << ' ';
	}
}

void merge(const std::string& file1, const std::string& file2)
{
	std::ifstream in_file(file1);
	if (!in_file)
	{
		error("Could not open '" + file1 + "' for reading.");
	}
	std::ifstream out_file(file2);
	if (!out_file)
	{
		error("Could not open '" + file1 + "' for reading.");
	}
	auto words1 = get_words(in_file);
	auto words2 = get_words(out_file);
	words2.insert(words2.end(), words1.begin(), words1.end());
	std::sort(words2.begin(), words2.end());
	write_sorted_words(file2, words2);
}

void print_help()
{
	std::cout << "Program merges contents of <file1> and <file2> into <file2>.\n"
		<< "To use it you must provide two parameters: <file1> <file2>.\n"
		<< "<file1> is an absolute or relative path to the file"
		<< "whose content will be appended to <file2>, i.e.\n"
		<< "C:\\Users\\user\Documents\\file1.txt\n"
		<< "<file2> is an absolute or relative path to file to whom"
		<< "contents of <file1> will be appended.\n";
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc == 2)
		{
			if (strcmp(argv[1], "help") == 0)
			{
				print_help();
				return 0;
			}
		}
		if (argc != 3)
		{
			error("Program expects 2 arguments: <file1> <file2>");
		}
		const char* file1{ argv[1] };
		const char* file2{ argv[2] };
		merge(file1, file2);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		std::cout << "Invoke with <help> parameter to print the help message.\n";
	}
}