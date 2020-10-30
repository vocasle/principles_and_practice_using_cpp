#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <cstring>
#include "utility.hpp"

void concatenate(const std::string& file1, const std::string& file2)
{
	std::ifstream in_file(file1);
	if (!in_file)
	{
		error("Could not open '" + file1 + "' for reading.");
	}
	std::ofstream out_file(file2, std::ios_base::app);
	if (!out_file)
	{
		error("Could not open '" + file1 + "' for writing.");
	}
	constexpr size_t buffer_size = 1024 * 1024;
	std::unique_ptr<char[]> buffer = std::make_unique<char[]>(buffer_size);
	while (in_file)
	{
		in_file.read(buffer.get(), buffer_size);
		out_file << buffer.get();
	}
}

void print_help()
{
	std::cout << "Program appends contents of <file1> to <file2>.\n"
		<< "To use it you must provide two parameters: <file1> <file2>\n"
		<< "where <file1> is an absolute or relative path to the file"
		<< "whose content will be appended to <file2>, i.e.\n"
		<< "C:\\Users\\user\Documents\\file1.txt\n"
		<< "and where <file2> is an absolute or relative path to file to whom"
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
		concatenate(file1, file2);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		std::cout << "Invoke with <help> parameter to print the help message.\n";
	}
}