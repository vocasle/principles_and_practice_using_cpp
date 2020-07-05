#include <iostream>
#include <cstdlib>

std::size_t strlen(const char* start) {
	const char* end = start;
	while (*end++ != 0);
	return end - start - 1;
}

char* strdup(const char* s)
{
	size_t length = strlen(s);
	char* ss = new char[length + 1];
	for (size_t i = 0; i < length; ++i)
		ss[i] = s[i];
	ss[length] = '\0';
	return ss;
}

int main()
{
	char* str1 = "HELLO, WORLD!";
	char* str2 = strdup(str1);
	std::cout << str1 << " == " << str2 << std::endl;
	delete[] str2;
}