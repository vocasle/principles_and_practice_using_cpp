#include <cinttypes>
// WARNING!!! This program leaks and causes OOM exception!

// in my case allocated memory raised to 33 GB until program crashed with
// Microsoft C++ exception: std::bad_alloc at memory location 0x0000006FDBBCFAA0.

int main()
{
	// will crash because of OOM
	while (true)
		char* ch = new char[INT32_MAX];
}