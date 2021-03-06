#include "Regular_polygon.hpp"

Regular_polygon::Regular_polygon(Point center, unsigned int circumradius, unsigned int n) :Polygon{ gen_poly(circumradius, n, calc_side_length(circumradius, n), center) }
{
	
}

// Generates N-sided polygon
// inradius - radius of incircle
// vertices - number of sides/vertices/angles
// side_length - length of the polygon's side
// center - center point of circle with radius inradius
Polygon gen_poly(int circumradius, int vertices, int side_length, const Point& center)
{
	auto points = vector<Point>();
	static constexpr auto pi = 3.14159265;
	for (auto n = 0; n < vertices; ++n)
	{
		auto x = circumradius * cos(2 * pi * n / vertices) + center.x;
		auto y = circumradius * sin(2 * pi * n / vertices) + center.y;
		points.emplace_back(x, y);
	}
	auto poly = Polygon{};
	for (auto& point : points)
	{
		poly.add(point);
	}
	return poly;
}

std::pair<Graph_lib::Point, Graph_lib::Point> find_third_vertex(
	const Graph_lib::Point& a,
	const Graph_lib::Point& b,
	int d_ac,
	int d_ab,
	int d_bc
)
{
	auto phi1 = atan2(a.y - b.y, a.x - b.x);
	auto phi2 = acos((pow(d_ac, 2) + pow(d_bc, 2) - pow(d_ab, 2)) / (2 * double(d_ac) * double(d_bc)));
	auto x1 = static_cast<int>(b.x + d_ac * cos(phi1 + phi2));
	auto x2 = static_cast<int>(b.x + d_ac * cos(phi1 - phi2));
	auto y1 = static_cast<int>(b.y + d_ac * sin(phi1 + phi2));
	auto y2 = static_cast<int>(b.y + d_ac * sin(phi1 - phi2));
	auto p1 = Graph_lib::Point{ x1, y1 };
	auto p2 = Graph_lib::Point{ x2, y2 };
	return std::pair<Graph_lib::Point, Graph_lib::Point>(p1, p2);
}

double calc_side_length(double circumradius, int vertices)
{
	static constexpr auto pi = 3.14159265;
	return 2 * circumradius * sin(pi / vertices);
}