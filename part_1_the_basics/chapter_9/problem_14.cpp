

#include "money.h"

int main()
{
	try
	{
		Money m{ 123.99, "EUR" };
		Money m2{ 45.01, "EUR" };
		std::cout << m << " + " << m2 << " = " << m + m2 << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}