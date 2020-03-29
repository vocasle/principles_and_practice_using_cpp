#include <vector>
#include <string>
#include <iostream>

void print(const std::string& label, const std::vector<int>& numbers)
{
	for (auto&& number : numbers)
		std::cout << label << ' ' << number << '\n';
}

int main()
{
	std::vector<int> numbers = { 1,2,3,4,5,6,7,8,9 };
	print("num", numbers);
	return 0;
}