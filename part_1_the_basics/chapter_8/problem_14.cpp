// This file contains solution for exercise 14 of chapter 8
//
// Passing argument by const value might be useful if you need to ensure
// that whoever is going to process that argument won't change it internal
// structure.
//
// I think that people don't use it often, because they don't need it.
// You can preserve original object unchanged if you pass by value.
// If you need to operate on large object you can pass it by const reference
// to prevent it from modifications.

struct MyStruct
{
	int i = 0;
};

void f(const MyStruct ms)
{
	//++i; won't compile, because i is const
	// std::cout << i << std::endl;
	// ms.i = 10;
}

int main()
{
	f(MyStruct());
	return 0;
}