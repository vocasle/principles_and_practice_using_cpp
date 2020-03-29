#include <iostream>

namespace X
{
	int var;
	void print()
	{
		std::cout << var << std::endl;
	}
}

namespace Y
{
	int var;
	void print()
	{
		std::cout << var << std::endl;
	}
}

namespace Z
{
	int var;
	void print()
	{
		std::cout << var << std::endl;
	}
}

int main()
{
	X::var = 7;
	X::print();
	using namespace Y;
	var = 9;
	print();
	{
		using Z::var;
		using Z::print;
		var = 11;
		print();
	}
	return 0;
}