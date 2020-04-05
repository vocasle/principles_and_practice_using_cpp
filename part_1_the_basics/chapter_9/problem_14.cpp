
#include <iostream>
#include "money.h"

int main()
{
	try
	{
		std::cout << "Welcome to money calculator.\n"
			<< "Enter first predicate: ";
		Money m{ 0, "EUR" };
		std::cin >> m;
		std::cout << "Enter second predicate: ";
		Money m2{ 0, "EUR" };
		std::cin >> m2;
		std::cout << m << " + " << m2 << " = " << m + m2 << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}