// This file contains a program that finds a word in file and prints
// the line that contains the word and its number

#include "chapter_11.hpp"
#include <fstream>

void print_found(const std::string& line, size_t num)
{
	std::cout << num << ": " << line << '\n';
}


void find_word_in_file(const std::string& filename, const std::string& word)
{
	std::ifstream file{ filename };
	if (!file)
	{
		error("Could not open '" + filename + "' for reading.");
	}
	std::string line;
	size_t line_num{ 1 };
	while (std::getline(file, line))
	{
		if (line.find(word) != std::string::npos)
		{
			print_found(line, line_num);
		}
		++line_num;
	}
}

int main()
{
	try
	{
		// annual-enterprise-survey-2018-financial-year-provisional-csv.csv
		auto filename = prompt_filename(FileType::in);
		auto word = prompt("Enter a word that you would like to find in the document.");
		find_word_in_file(filename, word);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}