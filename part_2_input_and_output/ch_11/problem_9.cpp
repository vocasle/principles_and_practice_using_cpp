#include "BinaryToText.hpp"
#include "TextToBinary.hpp"
#include "chapter_11.hpp"
#include <iostream>

void txt_to_bin(const std::string& from, const std::string& to)
{
	TextToBinary(from, to).convert();
}

void bin_to_txt(const std::string& from, const std::string& to)
{
	BinaryToText(from, to).convert();
}

int main()
{
	try
	{
		auto from = prompt_filename(FileType::in);
		auto to = prompt_filename(FileType::out);
		auto bin_from = prompt_filename(FileType::in);
		auto txt_to = prompt_filename(FileType::out);
		txt_to_bin(from, to);
		bin_to_txt(bin_from, txt_to);
		std::cout << "Done.\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}