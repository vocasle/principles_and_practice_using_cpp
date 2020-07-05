#include <iostream>

// For some reason on my machine objects allocated on stack grows up.
// Theoretically the addresses of stack-allocated objects should grow down to prevent
// collision with heap allocated objects.

int main()
{
	// some constexpr to allocate them on stack
	int int1 = 100;
	int int2 = 100;

	// some heap allocated objects
	int* i1 = new int(10);
	int* i2 = new int(20);

	std::cout << "nDoes stack grows up? " << (&int1 < &int2 ? "yep" : "no")
		<< "\nDoes heap grows up? " << (i1 < i2 ? "yep" : "no") << std::endl;

	delete i1;
	delete i2;
}