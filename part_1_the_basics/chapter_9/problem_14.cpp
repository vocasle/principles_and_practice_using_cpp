

#include "money.h"

int main()
{
	try
	{
		Money m{ "$123.25" };
		std::cout << m << " / " << 2 << " = " << m / 2 << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}