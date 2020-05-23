#include "Poly.hpp"

Poly::Poly(initializer_list<Point> points): Polygon()
{
	for (auto& p : points)
	{
		Polygon::add(p);
	}
}
