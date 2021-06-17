#include <iostream>
#include <sstream>
#include <cstring>

bool is_palindrome(const char s[], int n)
// s points to the first character of an array of n characters
{
	int first = 0;
	// index of first letter
	int last = n - 1;
	// index of last letter
	while (first < last) 
	{ // we haven’t reached the middle
		if (s[first] != s[last]) return false;
		++first;
		// move forward
		--last;
		// move backward
	}
	return true;
}

const char* read_fail_msg(int num_chars_to_read)
{
	std::ostringstream oss;
	oss << "\nERROR: Failed to read " 
		<< num_chars_to_read
		<< " characters from stdin.\n";
	return oss.str().c_str();
}

std::istream& read_word(std::istream& is, char* buffer, int max)
{
	// read at most max–1 characters from is into buffer
	is.width(max); // read at most max–1 characters in the next >>
	if (!(is >> buffer)) // read whitespace-terminated word,
	{
		throw std::runtime_error(read_fail_msg(max));
	}
	std::char_traits<char>::int_type res = is.peek();
	// check if there is more characters to read
	if (!std::isspace(res))
	{
		int size = 8;
		char* buf = new char[size];
		while(!std::isspace(res))
		{
			//std::ostringstream oss;
			//oss << "WARNING: There is more characters to read than "
			//	<< max << " characters specified to read.\n";
			//std::cout << oss.str() << std::endl;
			is.width(size);
			if (!(is >> buf))
			{
				throw std::runtime_error(read_fail_msg(size));
			}
		
			res = is.peek();
			strcat(buffer, buf);
		}
		delete[] buf;
	}

	// add zero after the last character read into buffer
	return is;
}

int main()
{
	constexpr int max = 128;
	try
	{
		for (char s[max]; read_word(std::cin,s,max); )
		{
			std::cout << s << " is";
			if (!is_palindrome(s,strlen(s))) 
			{
				std::cout << " not";
			}
			std::cout << " a palindrome\n";
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "Unknown exception\n";
		return EXIT_FAILURE;
	}
}
