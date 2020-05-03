#include "BinaryToText.hpp"
#include "chapter_11.hpp"

BinaryToText::BinaryToText(const std::string& from, const std::string& to):
	m_from{ from, std::ios::in | std::ios::binary }, m_to{ to }
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

BinaryToText::~BinaryToText()
{
}

void BinaryToText::convert()
{
	write_bytes(get_bytes());
}

std::vector<char> BinaryToText::get_bytes()
{
	auto bytes = std::vector<char>();
	for (auto byte = char{ 0 }; m_from.read(reinterpret_cast<char*>(&byte), sizeof byte);)
	{
		bytes.push_back(byte);
	}
	if (!m_from.good() && !m_from.eof())
	{
		error("Could not read file.");
	}
	return bytes;
}

void BinaryToText::write_bytes(const std::vector<char>& bytes)
{
	for (auto byte : bytes)
	{
		m_to.write(reinterpret_cast<char*>(&byte), sizeof byte);
	}
	if (!m_to.good())
	{
		error("Could not write to file.");
	}
}
