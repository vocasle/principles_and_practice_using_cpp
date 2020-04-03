//
// Created by Nikita Elsakov on 05.03.2020.
//
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

int main()
{
	std::vector<double> distances;
	std::cout << "Enter distances between city A and B separated by 'space'. "
			  << "To terminate input enter '.' and press 'enter':\n";
	for (double distance = 0; std::cin >> distance;)
	{
		distances.push_back(distance);
	}
	auto sum = std::accumulate(distances.begin(), distances.end(), 0.0);
	auto [min, max] = std::minmax_element(distances.begin(), distances.end());
	std::cout << "Total distance: "
			  << sum
			  << "\nThe smallest distance: " << *min
			  << "\nThe biggest distance: " << *max
			  << "\nThe mean distance: " << sum / distances.size();
	return 0;
}
