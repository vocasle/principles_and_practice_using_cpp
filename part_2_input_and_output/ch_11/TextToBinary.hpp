#ifndef TEXT_TO_BINARY_HPP
#define TEXT_TO_BINARY_HPP

#include <string>
#include <fstream>
#include <vector>

// TextToBinary converts text file to the binary file
class TextToBinary
{
public:
	TextToBinary(const std::string& from, const std::string& to);
	~TextToBinary();
	void convert();
private:
	std::ifstream m_from;
	std::ofstream m_to;
	std::vector<char> read_chars();
	void write_chars(const std::vector<char>& chars);
};

#endif // !TEXT_TO_BINARY_HPP
