#include "Right_triangle.hpp"

Right_triangle::Right_triangle(Point a, Point b, Point c): Polygon()
{
	if (!is_right_triangle(a, b, c))
	{
		error("Supplied points does not form a right triangle!");
	}
	Polygon::add(a);
	Polygon::add(b);
	Polygon::add(c);
}

bool is_right_triangle(Point a, Point b, Point c)
{
	auto distances = vector<double>();
	distances.push_back(distance(a, c));
	distances.push_back(distance(b, c));
	distances.push_back(distance(a, b));
	sort(distances.begin(), distances.end());
	auto hypotenuse = sqrt(pow(distances.at(0), 2) + pow(distances.at(1), 2));
	return abs(static_cast<int>(distances.at(2)) - static_cast<int>(hypotenuse)) < 5;
}

double distance(Point a, Point b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}
