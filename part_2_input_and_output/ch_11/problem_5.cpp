// This program reads a string and performs an analysis of the content
// For each character in the string it outputs character classification

#include "chapter_11.hpp"
#include <vector>

std::string read_line(std::istream& is)
{
	std::string line;
	std::getline(is, line);
	return line;
}

std::vector<std::string> classify_char(char ch)
{
	std::vector<std::string> classifications;
	if (isspace(ch))
	{
		classifications.push_back("whitespace");
	}
	if (isalpha(ch))
	{
		classifications.push_back("letter");
	}
	if (isdigit(ch))
	{
		classifications.push_back("decimal digit");
	}
	if (isxdigit(ch))
	{
		classifications.push_back("hexadecimal digit");
	}
	if (isupper(ch))
	{
		classifications.push_back("uppercase");
	}
	if (islower(ch))
	{
		classifications.push_back("lowercase");
	}
	if (isalnum(ch))
	{
		classifications.push_back("letter or decimal digit");
	}
	if (iscntrl(ch))
	{
		classifications.push_back("control character");
	}
	if (ispunct(ch))
	{
		classifications.push_back("punctuation character");
	}
	if (isprint(ch))
	{
		classifications.push_back("printable");
	}
	if (isgraph(ch))
	{
		classifications.push_back("visible");
	}
	return classifications;
}

void print_classification(std::ostream& os, const std::string& str)
{
	for (auto& ch : str)
	{
		os << ch << " - ";
		for (auto& classification : classify_char(ch))
		{
			os << classification << " | ";
		}
		os << '\n';
	}
}


int main()
{
	std::cout << "Enter a string and press \"Enter\".\n";
	auto str = read_line(std::cin);
	print_classification(std::cout, str);
}