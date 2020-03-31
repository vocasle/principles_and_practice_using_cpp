#include <vector>
#include <algorithm>

std::vector<int32_t> reverse(const std::vector<int32_t>& v)
{
	std::vector<int32_t> reversed;
	for (auto it = v.rbegin(); it != v.rend(); ++it)
		reversed.push_back(*it);
	return reversed;
}

void reverse(std::vector<int32_t>& v)
{
	std::reverse(v.begin(), v.end());
}