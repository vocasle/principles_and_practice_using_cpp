#include "chapter_8.h"

template <typename T>
T maxv(const std::vector<T>& v)
{
	if (v.size() == 0)
		error("vector is empty");
	auto it = v.begin();
	auto max = *it;
	for (; it != v.end(); ++it)
		if (max < *it)
			max = *it;
	return max;
}