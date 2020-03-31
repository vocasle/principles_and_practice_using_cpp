#include <vector>
#include <string>
#include <stdexcept>

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

void fibonacci(int32_t first, int32_t second, std::vector<int32_t>& numbers, int32_t numOfElements)
{
	// Fn = Fn-1 + Fn-2
	if (first < 0 || second < 0 || numOfElements < 0)
		error("'first' or 'second' or 'numOfElements' must be nonnegative");
	if (numOfElements == 0)
		return;
	numbers.push_back(first);
	numbers.push_back(second);
	auto fn_1 = first;
	auto fn_2 = second;
	for (; numbers.size() != numOfElements;)
	{
		auto fn = fn_1 + fn_2;
		numbers.push_back(fn);
		fn_1 = fn_2;
		fn_2 = fn;
	}
}