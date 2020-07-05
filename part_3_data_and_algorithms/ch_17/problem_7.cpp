#include <iostream>

void strcpy(char* from, char* to)
{
	while (*from)
		*(to++) = *(from++);
}

size_t strlen(char* s)
{
	size_t i = 0;
	for (; s[i] != '\0'; ++i);
	return i;
}

// reads characters from istream into array of char
// array of chars will grow dynamically
char* read_from_is(std::istream& is, char terminator = '!')
{
	size_t length = 10;
	char* str = new char[length];
	char* begin = str;
	while (is.get(*str) && *(str++) != terminator)
	{
		if (str - begin == length - 1)
		{
			*(begin + (str - begin)) = '\0';
			length = length * length;
			str = new char[length];
			size_t l = strlen(begin);
			strcpy(begin, str);
			delete[] begin;
			begin = str;
			str += l;
		}
	}
	*str = '\0';
	return begin;
}

int main()
{
	char* str = read_from_is(std::cin);
	std::cout << str << std::endl;
	delete[] str;
}