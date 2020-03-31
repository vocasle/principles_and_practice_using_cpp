#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

template <typename T>
void print(const std::string& label, const std::vector<T>& numbers)
{
	for (auto&& number : numbers)
		std::cout << label << ' ' << number << '\n';
}

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

template <typename T>
VectorData get_vector_data(const std::vector<T>& numbers)
{
	if (numbers.size() == 0)
		error("vector is emtpy");
	// consult http://www.stroustrup.com/bs_faq2.html#constraints
	Can_copy<T, double>(); // accept only numeric types
	auto it = numbers.begin();
	auto vd = VectorData();
	vd.max = *it;
	vd.min = *it;
	double sum = *it;

	if (numbers.size() == 1)
	{
		vd.min = vd.median = vd.mean = vd.max;
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

	std::vector<T> copy_of_v(numbers);
	std::sort(copy_of_v.begin(), copy_of_v.end());

	vd.mean = sum / numbers.size();
	size_t pos = numbers.size() / 2;
	if (numbers.size() % 2 == 0)
	{
		double upper = numbers.at(pos);
		double lower = numbers.at(pos - 1);
		vd.median = (upper + lower) / 2.0;
	}
	else
		vd.median = numbers.at(pos);

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