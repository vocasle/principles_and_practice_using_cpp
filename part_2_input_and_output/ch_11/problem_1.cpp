// This file contains a program that converts content of input file
// to lowercase and stores it in output file

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <memory>
#include <sstream>

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

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
	constexpr size_t buffer_size = 1024 * 1024;
	std::unique_ptr<char[]> buffer = std::make_unique<char[]>(buffer_size);
	while (in_file)
	{
		in_file.read(buffer.get(), buffer_size);
		out_file << to_lower(buffer.get());
	}
}

enum class FileType
{
	in, out
};

std::string prompt_filename(const FileType& type)
{
	std::cout << "Please enter the name of the " 
		<< (type == FileType::in ? "in" : "out")
		<< " file: ";
	std::string filename;
	std::getline(std::cin, filename);
	return filename;
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
