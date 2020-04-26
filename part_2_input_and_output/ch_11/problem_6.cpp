// This program replaces | . | ; | , | ? | - | ' | characters with whitespace character
// in the file and prints contents of the file without those characters.
// If a text is found within a pair of double quotes the text will be left unprocessed.
//
// Edit 1: Exercise 6

#include "chapter_11.hpp"

#include <sstream>
#include <fstream>

std::string replace_punct(const std::string& str)
{
	std::ostringstream oss;
	size_t offset{ 0 };
	for (auto it = str.begin(); it != str.end();)
	{
		if (ispunct(*it))
		{
			if (*it == '"')
			{
				size_t pos = it - str.begin();
				if (pos != std::string::npos && *it == '"')
				{
					size_t next = str.find(*it, pos + 1);
					if (next != std::string::npos)
					{
						auto substr = str.substr(pos, next + 1 - pos);
						oss << substr;
						it += substr.size();
						offset = next + 1;
					}
					else
					{
						++it;
					}
				}
			}
			else
			{
				oss << ' ';
				++it;
			}
		}
		else
		{
			oss << *it;
			++it;
		}
	}
	return oss.str();
}

int main()
{
	auto filename = prompt_filename(FileType::in);
	std::ifstream file{ filename };
	if (!file)
	{
		std::cerr << "Could not open file '" << filename << "' for reading.";
		return -1;
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::cout << replace_punct(line) << '\n';
	}
}