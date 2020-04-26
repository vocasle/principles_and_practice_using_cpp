// This program removes vowels from the file

#include "chapter_11.hpp"

#include <fstream>
#include <sstream>

bool is_vowel(char ch)
{
	switch (static_cast<char>(std::tolower(ch)))
	{
	case 'a':
	case 'e':
	case 'i':
	case 'o':
	case 'u':
	case 'y':
		return true;
	default:
		return false;
	}
}

std::string remove_vowels(const std::string& line)
{
	std::ostringstream oss;
	for (auto& ch : line)
	{
		if (!is_vowel(ch))
		{
			oss << ch;
		}
	}
	return oss.str();
}

void remove_vowels_from_file()
{
	auto in = prompt_filename(FileType::in);
	auto out = prompt_filename(FileType::out);
	std::ifstream in_file{ in };
	if (!in_file)
	{
		file_open_err(in, FileType::in);
	}
	std::ofstream out_file{ out };
	if (!out_file)
	{
		file_open_err(out, FileType::out);
	}
	std::string line;
	while (std::getline(in_file, line))
	{
		out_file << remove_vowels(line) << '\n';
	}
}

int main()
{
	remove_vowels_from_file();
}