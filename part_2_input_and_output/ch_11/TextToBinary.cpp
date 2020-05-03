#include "TextToBinary.hpp"
#include "chapter_11.hpp"

TextToBinary::TextToBinary(const std::string& from, const std::string& to) :
	m_from{from}, m_to{ to, std::ios::binary | std::ios::out }
{
	if (!m_from)
	{
		error("Could not open '" + from + "' for reading.");
	}
	if (!m_to)
	{
		error("Could not open '" + to + "' for writing.");
	}
	m_from.exceptions(m_from.exceptions() | std::ios::badbit);
	m_to.exceptions(m_from.exceptions() | std::ios::badbit);
}

TextToBinary::~TextToBinary()
{
}

void TextToBinary::convert()
{
	write_chars(read_chars());
}

std::vector<char> TextToBinary::read_chars()
{
	auto chars = std::vector<char>();
	for (char ch; m_from.get(ch);)
	{
		chars.push_back(ch);
	}
	if (!m_from.good() && !m_from.eof())
	{
		error("Could not read from file.");
	}
	return chars;
}

void TextToBinary::write_chars(const std::vector<char>& chars)
{
	for (auto ch : chars)
	{
		m_to.write(reinterpret_cast<char*>(&ch), sizeof ch);
	}
	if (!m_to.good())
	{
		error("Could not write to file.");
	}
}
