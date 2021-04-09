/*
 * This file contains solution for exercise 9
 * 
 * On my machine:
 * static storage grows up
 * stack storage grows down
 * heap storage grows up
 * elements in heap array with higher indices have bigger address
 */

#include <iostream>

int GI_ONE = 1;
int GI_TWO = 2;
int GI_THREE = 3;

void stack_three();

void stack_two()
{
	int two = 20;
	std::cout << "\n&two=" << &two;
	stack_three();
}

void stack_three()
{
	int three = 30;
	std::cout << "\n&three=" << &three;
}

void func_free()
{
	int* one = new int;
	*one = 100;
	int* two = new int;
	*two = 200;
	int* three = new int;
	*three = 300;

	std::cout << "\nMemory addresses on heap:"
		<< "\n&one=" << &one
		<< "\n&two=" << &two
		<< "\n&three=" << &three
		<< std::endl;

	delete one;
	delete two;
	delete three;
}

void func_static();

void func_stack()
{
	int one = 10000;
	/* Please note that addresses for &one, &two and &three differ
	 * only because stack_two is called from stack_one and
	 * stack_three is called from stack_two.
	 * If we call all thee function from func_stack
	 * the result will be different.
	 */
	std::cout << "\nMemory addresses on stack:";
	std::cout << "\n&one=" << &one;
	stack_two();
	std::cout << std::endl;

	/*
	 * Here you can see that address of &three is different
	 * when stack_three is invoked from func_stack and stack_two
	 */
	std::cout << "\nMemory addresses on stack called from func_stack:";
	stack_three();
	stack_two();
	std::cout << std::endl;

	// Static storage does not move like stack does
	func_static();
}

void func_static()
{
	std::cout << "\nMemory addresses on static:"
	<< "\n&one=" << &GI_ONE
	<< "\n&two=" << &GI_TWO
	<< "\n&three=" << &GI_THREE
	<< std::endl;
}

void func_arr()
{
	constexpr unsigned int size = 100;
	int* arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = i;
	}
	std::cout << "\nMemory addresses in array:";
	for (int i = 0; i < size; i += 10)
	{
		std::cout << "\n&arr[" << i << "] = " << &arr[i];
	}
	std::cout << std::endl;
	delete[] arr;
}


int main()
{
	func_static();
	func_stack();
	func_free();
	func_arr();
}