// This file contains a program that converts content of input file
// to lowercase and stores it in output file

#include <fstream>
#include <sstream>

#include "chapter_11.hpp"


std::string to_lower(const std::string& line)
{
	std::ostringstream oss;
	for (auto& ch : line)
	{
		oss << static_cast<char>(std::tolower(ch));
	}
	return oss.str();
}

void file_to_lower(const std::string& in_filename, const std::string& out_filename)
{
	std::ifstream in_file{ in_filename };
	if (!in_file)
	{
		error("Could not open file '" + in_filename + "' for reading.");
	}
	std::ofstream out_file{ out_filename };
	if (!out_file)
	{
		error("Could not open file '" + in_filename + "' for reading.");
	}
	std::string line;
	while (std::getline(in_file, line))
	{
		out_file << to_lower(line) << '\n';
	}
}

int main()
{
	try
	{
		auto input = prompt_filename(FileType::in);
		auto output = prompt_filename(FileType::out);
		file_to_lower(input, output);
		std::cout << "All content from " << input
			<< " was converted to lowercase and saved to "
			<< output << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
