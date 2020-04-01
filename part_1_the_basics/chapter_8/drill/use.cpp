#include "my.h"
#include <iostream>

int foo = 7;

int main()
{
	print_foo();
	print(99);

	int x = 7;
	int y = 9;
	// arguments passed by value, there is no need to check with cout
	// because we won't see the changes
	swap_v(x, y);
	swap_r(x, y);
	std::cout << "x: " << x << ", y: " << y << '\n';

	// arguments passed by value, there is no need to check with cout
	// because we won't see the changes
	swap_v(7, 9);
	// won't compile, because 7 and 9 are rvalues
	//swap_r(7, 9);

	const int cx = 7;
	const int cy = 9;
	swap_v(cx, cy);
	std::cout << "cx: " << cx << ", cy: " << cy << '\n';
	// won't compile, because cx and cy are constant lvalues
	//swap_r(cx, cy);

	// arguments passed by value, there is no need to check with cout
	// because we won't see the changes
	swap_v(7.7, 9.9);
	// won't compile, because 7.7 and 9.9 are rvalues
	//swap_r(7.7, 9.9);

	double dx = 7.7;
	double dy = 9.9;
	// arguments passed by value, there is no need to check with cout
	// because we won't see the changes
	swap_v(dx, dy);
	// won't compile because swap_r expects int&
	//swap_r(dx, dy);
	
	return 0;
}