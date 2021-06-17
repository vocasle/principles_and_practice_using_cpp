#include <cstring>
#include <iostream>

char* findx(const char* s, const char* x)
{
	for (size_t i = 0; s[i] != 0; ++i)
	{
		if (s[i] == *x)
		{
			bool found = true;
			for (size_t j = 0; x[j] != 0 && s[i + j] != 0; ++j)
				found = found && s[i + j] == x[j];
			if (found)
			{
				size_t length = strlen(x);
				char* str = new char[i + length + 1];
				for (size_t n = 0; n < i + length; ++n)
					str[n] = s[n];
				str[i + length] = '\0';
				return str;
			}
		}
	}
	return nullptr;
}

int main()
{
	const char* str = "Hello, world, this is a beautifull world!";
	char* substr = findx(str, "world!");
	if (substr)
	{
		std::cout << substr << '\n';
	}
	delete[] substr;
}
