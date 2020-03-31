// This file contains solution for exercise 11 of chapter 8
//
// I have chosen to return one struct instead of using 4 references to doubles.
// This way signature of get_vector_data is much simpler and in my opinion 
// is simpler to use.
// The struct that will be returned from get_vector_data is not too big, because 
// it holds 4 doubles and is quite chip to copy.

#include "chapter_8.h"

int main()
{
	try
	{
		std::vector<int32_t> i32v{
			1,2,3,4,5,6,7,8,9,10
		};

		std::vector<int64_t> i64v{
			1,2,3,4,5,6,7,8,9,10
		};

		std::vector<char> cv{
			'a', 'b', '$', 'C', 'd', 'e', 'Z', 'z'
		};

		std::vector<double> dv{
			3.14, 2.18, 1.8, 3.10, 2.22, 2.8, 6.28
		};

		std::vector<int8_t> i8v{
			'a'
		};

		std::vector<int> iv;

		print_vector_data(get_vector_data(i32v));
		print_vector_data(get_vector_data(i64v));
		print_vector_data(get_vector_data(cv));
		print_vector_data(get_vector_data(dv));
		print_vector_data(get_vector_data(i8v));
		print_vector_data(get_vector_data(iv));
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}