#include "my.h"
#include "std_lib_facilities.h"

void print_foo()
{
	cout << foo << '\n';
}

void print(int i)
{
	cout << i << '\n';
}

void swap_v(int a, int b)
{
	int temp; 
	temp = a;
	a = b; 
	b = temp;
}

void swap_r(int& a, int& b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

// won't compile
//void swap_cr(const int& a, const int& b)
//{
//	int temp;
//	temp = a;
//	a = b;
//	b = temp;
//}