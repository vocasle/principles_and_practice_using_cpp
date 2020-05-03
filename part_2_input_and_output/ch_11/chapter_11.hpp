#ifndef CHAPTER_11_HPP
#define CHAPTER_11_HPP
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

enum class FileType
{
	in, out
};

void error(const std::string& msg);

template<typename T>
void print_vector(const std::vector<T>& vec, char delim = '\n');

bool starts_with(const std::string& str, char ch);

bool ends_with(const std::string& str, char ch);

// converts all characters to lower case
std::string to_lower(const std::string& line);

void file_open_err(const std::string& filename, FileType type);

std::string prompt_filename(const FileType& type);

std::string prompt(const std::string& msg);

std::string capitalize(const std::string& str);

// splits string str into vector of strings
std::vector<std::string> split(const std::string& str, const std::string& delim = " ");
#endif // !CHAPTER_11_HPP
