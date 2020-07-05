#include <iostream>

void to_lower(char* s)
{
	constexpr char distance = 'a' - 'A';
	if (s)
	{
		for (size_t i = 0; s[i] != 0; ++i)
			if (s[i] >= 'A' && s[i] <= 'Z')
				s[i] = s[i] + distance;
	}
}

int main()
{
	char* str = new char[14]{ "HELLO, WORLD!" };
	std::cout << "Original: " << str << '\n';
	to_lower(str);
	std::cout << "\nLowercased: " << str << '\n';
	delete[] str;
}