#include "chapter_11.hpp"

#include <fstream>

struct CharType
{
	uint32_t whitespace;
	uint32_t letter;
	uint32_t dec_dig;
	uint32_t hex_dig;
	uint32_t uppercase;
	uint32_t lowercase;
	uint32_t let_dig;
	uint32_t ctrl_ch;
	uint32_t punct_ch;
	uint32_t printable;
	uint32_t visible;
};

void classify_char(char ch, CharType& ct)
{
	std::vector<std::string> classifications;
	if (isspace(ch))
	{
		++ct.whitespace;
	}
	if (isalpha(ch))
	{
		++ct.letter;
	}
	if (isdigit(ch))
	{
		++ct.dec_dig;
	}
	if (isxdigit(ch))
	{
		++ct.hex_dig;
	}
	if (isupper(ch))
	{
		++ct.uppercase;
	}
	if (islower(ch))
	{
		++ct.lowercase;
	}
	if (isalnum(ch))
	{
		++ct.let_dig;
	}
	if (iscntrl(ch))
	{
		++ct.ctrl_ch;
	}
	if (ispunct(ch))
	{
		++ct.punct_ch;
	}
	if (isprint(ch))
	{
		++ct.printable;
	}
	if (isgraph(ch))
	{
		++ct.visible;
	}
}

CharType count_char_types(const std::string& filename)
{
	auto file = std::ifstream{ filename };
	if (!file)
	{
		file_open_err(filename, FileType::in);
	}
	auto ct = CharType{};
	for (auto ch = char(); file.get(ch);)
	{
		classify_char(ch, ct);
	}
	if ((file.fail() || file.bad()) && !file.eof())
	{
		error("An error occured while reading data from " + filename);
	}
	return ct;
}

void print_result(const CharType& ct)
{
	std::cout << "Whitespace: \t\t\t" << ct.whitespace
		<< "\nLetter: \t\t\t" << ct.letter
		<< "\nDecimal digit: \t\t\t" << ct.dec_dig
		<< "\nHexadecimal digit: \t\t" << ct.hex_dig
		<< "\nUppercase: \t\t\t" << ct.uppercase
		<< "\nLowercase: \t\t\t" << ct.lowercase
		<< "\nLetter or decimal digit: \t" << ct.let_dig
		<< "\nControl character: \t\t" << ct.ctrl_ch
		<< "\nPunctuation character: \t\t" << ct.punct_ch
		<< "\nPrintable: \t\t\t" << ct.printable
		<< "\nVisible: \t\t\t" << ct.printable;
}

int main()
{
	auto filename = prompt_filename(FileType::in);
	try
	{
		print_result(count_char_types(filename));
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}