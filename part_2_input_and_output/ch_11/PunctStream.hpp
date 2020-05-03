#ifndef PUNCT_STREAM_HPP
#define PUNCT_STREAM_HPP
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <map>
#include <functional>

// PunctStream allows to register callback functions for specific characters
// the callback function has to have signature: 
// void my_callback(std::string&, std::string::const_iterator&)
using callback = std::function<void(std::string&, std::string::const_iterator&)>;

// PunctStream allows to read from source (file or another std::istream) line by line.
// Each line is processed character by character. If character is one of chars in m_repl_list
// than it will be replaced with replacement character m_repl_char.
// It is possible to register a callback function for specific character. This character
// must be one of the characters in m_repl_list. It a responsibility of the user to
// handle characters that have callback functions.
class PunctStream
{
public:
	PunctStream(
		std::istream& source, 
		const std::string& ignore_list, 
		bool is_case_sensitive = true,
		char repl_char = ' '
	);
	~PunctStream();
	void register_callback(callback cb, char ch);
	PunctStream& operator>>(std::string& str);
	operator bool();
	bool is_whitespace(char ch) const;
private:
	std::map<char, callback> m_callbacks;
	std::istream& m_src;
	std::string m_repl_list;
	std::istringstream m_buffer;
	char m_repl_char;
	bool m_is_case_sens;
	bool has_callback(char ch) const;
};

bool contains(const std::string& str, const std::string& s, size_t hint = 0);
void error(const std::string& msg);

// this functions finds position of character that fails condition of function fn
size_t find_left(const std::string& str, size_t pos, std::function<bool(char)> fn);
// this functions finds position of character that fails condition of function fn
size_t find_right(const std::string& str, size_t pos, std::function<bool(char)> fn);
bool replace(std::string& str, const std::string& from, const std::string& to);
void remove_duplicates(std::vector<std::string>& words);

#endif // !PUNCT_STREAM_HPP
