#include <iostream>
#include <vector>


void print_array(std::ostream& os, int* a, int size)
{
	for (int i = 0; i < size; ++i)
		os << a[i] << ' ';
}

void print_vector(std::ostream& os, std::vector<int>* vec)
{
	for (int i = 0; i < vec->size(); ++i)
		os << vec->at(i) << ' ';
}

int main()
{
	constexpr int size = 20;
	int* ints = new int[size];

	for (int i = 0; i < size; ++i)
		ints[i] = 100 + i;
	print_array(std::cout, ints, size);
	std::cout << std::endl;
	delete[] ints;

	std::vector<int>* vec = new std::vector<int>(size);
	for (int i = 0; i < size; ++i)
		vec->at(i) = 100 + i;
	print_vector(std::cout, vec);
	std::cout << std::endl;
	delete vec;

	int i = 7;
	int* p1 = &i;
	std::cout << "p1=" << p1 << ", i=" << *p1 << '\n';

	constexpr int arr_size = 7;
	int* arr = new int[arr_size];
	for (int i = 0; i < arr_size; ++i)
		arr[i] = i + 1;
	int* p2 = &arr[0];
	std::cout << "p2=" << p2 << ", arr=[";
	print_array(std::cout, arr, arr_size);
	std::cout << "]\n";

	int* p3 = p2;
	p2 = p1;
	p2 = p3;

	std::cout << "p1=" << p1 << ", *p1=" << *p1 << '\n';
	std::cout << "p2=" << p2 << ", *p2=[";
	print_array(std::cout, p2, arr_size);
	std::cout << "]\n";
	delete[] arr;

	int* iarr = new int[10];
	p1 = &iarr[0];
	int* iarr2 = new int[10];
	p2 = &iarr2[0];
	for (int i = 0; i < 10; ++i)
	{
		p1[i] = i + 1;
		p2[i] = p1[0];
	}

	std::vector<int> vec1(10);
	std::vector<int> vec2(10);
	p1 = &vec1[0];
	p2 = &vec2[0];
	for (int i = 0; i < 10; ++i)
	{
		p1[i] = i + 1;
		p2[i] = p1[0];
	}
}