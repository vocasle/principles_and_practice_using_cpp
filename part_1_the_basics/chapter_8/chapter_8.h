#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

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

template <typename T>
struct VectorData
{
	T max;
	T min;
	T mean;
	T median;
};

template <typename T>
VectorData<T> get_vector_data(const std::vector<T>& v)
{
	auto vectorData = VectorData<T>();
	return vectorData;
}