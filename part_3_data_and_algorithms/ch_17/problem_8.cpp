#include <iostream>
#include <string>

std::string read_from_is(std::istream& is, char terminator = '!')
{
	std::string str;
	char ch = 0;
	while (is.get(ch) && ch != terminator)
		str += ch;
	return str;
}

int main()
{
	std::string str = read_from_is(std::cin);
	std::cout << str << std::endl;
}