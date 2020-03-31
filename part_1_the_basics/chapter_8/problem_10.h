template <typename T>
T maxv(const std::vector<T>& v)
{
	auto max = T();
	for (auto it = v.begin(); it != v.end(); ++it)
		if (max < *it)
			max = *it;
	return max;
}