#include <vector>
#include <algorithm>

template <typename T>
std::vector<T> reverse(const std::vector<T>& v)
{
	std::vector<T> reversed;
	for (auto it = v.rbegin(); it != v.rend(); ++it)
		reversed.push_back(*it);
	return reversed;
}

template <typename T>
void reverse(std::vector<T>& v)
{
	std::reverse(v.begin(), v.end());
}