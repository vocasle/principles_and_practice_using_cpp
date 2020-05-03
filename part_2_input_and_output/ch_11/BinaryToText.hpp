#ifndef BINARY_TO_TEXT_HPP
#define BINARY_TO_TEXT_HPP

#include <string>
#include <fstream>
#include <vector>

// BinaryToText converts binary file to the text file
class BinaryToText
{
public:
	BinaryToText(const std::string& from, const std::string& to);
	~BinaryToText();
	void convert();
private:
	std::ifstream m_from;
	std::ofstream m_to;
	std::vector<char> get_bytes();
	void write_bytes(const std::vector<char>& bytes);
};

#endif // !BINARY_TO_TEXT_HPP
