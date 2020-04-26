#include <stdexcept>
#include <string>
#include <iostream>

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
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

std::string prompt(const std::string& msg)
{
	std::cout << msg << ": ";
	std::string line;
	std::getline(std::cin, line);
	return line;
}