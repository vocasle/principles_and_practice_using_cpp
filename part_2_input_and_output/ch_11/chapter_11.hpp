#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

enum class FileType
{
	in, out
};

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

bool starts_with(const std::string& str, char ch)
{
	return !str.empty() && str.at(0) == ch;
}

bool ends_with(const std::string& str, char ch)
{
	return !str.empty() && str.at(str.size() - 1) == ch;
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

void file_open_err(const std::string& filename, FileType type)
{
	error("Could not open '" 
		+ filename 
		+ "' for " 
		+ (type == FileType::in ? "reading" : "writing"));
}


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