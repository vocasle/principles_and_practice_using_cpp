// This file contains solution for exercise 11 of chapter 8
//
// I have chosen to return one struct instead of using 4 references to doubles.
// This way signature of get_vector_data is much simpler and in my opinion 
// is simpler to use.
// The struct that will be returned from get_vector_data is not too big, because 
// it holds 4 doubles and is quite chip to copy.

#include "chapter_8.h"

struct VectorData
{
	double max;
	double min;
	double mean;
	double median;
};

template<typename T1, typename T2>
struct Can_copy {
	static void constraints(T1 a, T2 b)
	{
		T2 c = a;
		b = a;
	}
	Can_copy()
	{
		void(*p)(T1, T2) = constraints;
	}
};
template <typename Number>
VectorData find_max_min_mean(const std::vector<Number>& numbers)
{
	VectorData vd;

	auto it = numbers.begin();
	vd.max = *it;
	vd.min = *it;
	double sum = *it;

	if (numbers.size() == 1)
	{
		vd.min = vd.mean = vd.max;
		return vd;
	}

	for (it = it + 1; it != numbers.end(); ++it)
	{
		if (vd.max < *it)
			vd.max = *it;
		if (vd.min > * it)
			vd.min = *it;
		sum += *it;
	}

	vd.mean = sum / numbers.size();
	return vd;
}

template <typename Number> 
void find_median(const std::vector<Number>& numbers,
	VectorData& vd)
{
	if (numbers.size() == 1)
	{
		vd.median = numbers.at(0);
		return;
	}

	std::vector<Number> numbers_copy(numbers);
	std::sort(numbers_copy.begin(), numbers_copy.end());

	size_t pos = numbers.size() / 2;
	vd.median = numbers.at(pos);

	if (numbers.size() % 2 == 0)
	{
		double upper = numbers.at(pos);
		double lower = numbers.at(pos - 1);
		vd.median = (upper + lower) / 2.0;
	}
}


template <typename Number>
VectorData get_vector_data(const std::vector<Number>& numbers)
{
	if (numbers.size() == 0)
		error("vector is emtpy");
	// consult http://www.stroustrup.com/bs_faq2.html#constraints regarding Can_copy
	Can_copy<Number, double>(); // accept only numeric types
	auto vd = find_max_min_mean(numbers);
	find_median(numbers, vd);
	return vd;
}

void print_vector_data(const VectorData& vd)
{
	std::cout << "Max element: " << vd.max
		<< "\nMin element: " << vd.min
		<< "\nMedian: " << vd.median
		<< "\nMean: " << vd.mean
		<< '\n';
}

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