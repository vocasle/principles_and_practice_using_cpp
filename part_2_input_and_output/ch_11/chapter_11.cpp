#include "chapter_11.hpp"

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

template<typename T>
void print_vector(const std::vector<T>& vec, char delim)
{
	for (const T& el : vec)
	{
		std::cout << el << delim;
	}
}

bool starts_with(const std::string& str, char ch)
{
	return !str.empty() && str.at(0) == ch;
}

bool ends_with(const std::string& str, char ch)
{
	return !str.empty() && str.at(str.size() - 1) == ch;
}

// converts all characters to lower case
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

std::string capitalize(const std::string& str)
{
	std::ostringstream oss;
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if (it == str.begin())
		{
			oss << static_cast<char>(toupper(*it));
		}
		else
		{
			oss << static_cast<char>(tolower(*it));
		}
	}
	return oss.str();
}

// splits string str into vector of strings
std::vector<std::string> split(const std::string& str, const std::string& delim)
{
	auto word = std::string{};
	auto words = std::vector<std::string>{};
	auto offset = 0u;
	auto pos = 0u;
	for (auto pos = str.find(delim, offset); pos != std::string::npos;)
	{
		auto substr = str.substr(offset, pos - offset);
		words.push_back(substr);
		offset = pos + 1;
		pos = str.find(delim, offset);
	}
	words.push_back(str.substr(offset, pos - offset));
	return words;
}