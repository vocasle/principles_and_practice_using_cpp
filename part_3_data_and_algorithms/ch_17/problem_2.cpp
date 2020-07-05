#include <iostream>

int main()
{
	std::cout << "On Windows double takes 8 bytes, int takes 4 bytes and bool takes 1 byte\n";
	std::cout << "On this OS\n"
		<< "double takes " << sizeof(double) << " bytes\n"
		<< "int takes " << sizeof(int) << " bytes\n"
		<< "bool takes " << sizeof(bool) << " bytes\n";
}