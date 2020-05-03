#include "PunctStream.hpp"
#include <algorithm>

PunctStream::PunctStream(
	std::istream& source, 
	const std::string& ignore_list, 
	bool is_case_sensitive,
	char repl_char
)
	: m_src{source},
	m_repl_list{ignore_list}, 
	m_is_case_sens{is_case_sensitive},
	m_repl_char{repl_char}
{
}

PunctStream::~PunctStream()
{
}

// checks wether callback for character ch was registered
bool PunctStream::has_callback(char ch) const
{
	return m_callbacks.find(ch) != m_callbacks.end();
}

PunctStream& PunctStream::operator>>(std::string& str)
{
	// we go into the loop only if m_buffer is empty
	while (!(m_buffer >> str))
	{
		if (m_buffer.bad() || !m_src.good())
		{
			return *this;
		}
		m_buffer.clear();

		std::string line;
		std::getline(m_src, line);
		// process the line from the source (e.g. file or std::cin)
		for (auto it = line.begin(); it != line.end();)
		{
			if (is_whitespace(*it))
			{
				if (has_callback(*it))
				{
					// callback is called for character
					// it is responsibility of user to move update contents of the string
					// line and move iterator it forward/backward
					m_callbacks[*it](line, it);
				}
				else
				{
					*it = m_repl_char;
					++it;
				}
			}
			else if(!m_is_case_sens)
			{
				*it = tolower(*it);
				++it;
			}
			else
			{
				++it;
			}
		}
		m_buffer.str(line);
	}
	return *this;
}

// checking wether character ch is one of the characters that must be converted to whitespace
bool PunctStream::is_whitespace(char ch) const
{
	for (auto& ic : m_repl_list)
	{
		if (ic == ch)
		{
			return true;
		}
	}
	return false;
}

// allows to cast PunctStream to bool
PunctStream::operator bool()
{
	return !(m_src.bad() || m_src.fail()) && !(m_buffer.bad() || m_buffer.fail());
}

// registers callback for character ch
// when PunctStream's >> operator will find the character ch
// it will call the callback
void PunctStream::register_callback(callback cb, char ch)
{
	m_callbacks[ch] = cb;
}

// --- helper functions ---

// checks wether string str contais substring s
// if hint is provided the search will be started from hint
bool contains(const std::string& str, const std::string& s, size_t hint)
{
	if (hint != 0)
	{
		if (hint > str.size())
		{
			error("Hint is out of bounds.");
		}
		return str.substr(hint, str.size() - hint).find(s) != std::string::npos;
	}
	return str.find(s) != std::string::npos;
}

// finds first character that does not pass fn predicate
size_t find_left(const std::string& str, size_t pos, std::function<bool(char)> fn)
{
	if (pos > str.size() || pos == 0)
	{
		error("Position is out of bounds.");
	}

	for (auto it = str.begin() + pos - 1; it != str.begin(); --it)
	{
		if (!fn(*it))
		{
			return it - str.begin();
		}
	}
	return 0;
}

// finds first character that does not pass fn predicate
size_t find_right(const std::string& str, size_t pos, std::function<bool(char)> fn)
{
	if (pos >= str.size())
	{
		error("Position is out of bounds.");
	}
	for (auto it = str.begin() + pos + 1; it != str.end(); ++it)
	{
		if (!fn(*it))
		{
			return it - str.begin();
		}
	}
	return str.size();
}

// replaces substring from of string str with string to
bool replace(std::string& str, const std::string& from, const std::string& to)
{
	auto pos = str.find(from);
	if (pos == std::string::npos)
	{
		return false;
	}
	str.replace(pos, from.size(), to);
	return true;
}


void remove_duplicates(std::vector<std::string>& words)
{
	words.erase(std::unique(words.begin(), words.end()), words.end());
}