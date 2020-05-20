#ifndef REGULAR_POLYGON_HPP
#define REGULAR_POLYGON_HPP
#include <graphics/Graph.h>

using namespace Graph_lib;

class Regular_polygon : public Polygon
{
public:
	Regular_polygon(Point center, unsigned int circumradius, unsigned int n);
};

// Generates N-sided polygon
// circumradius - radius of excircle
// vertices - number of sides/vertices/angles
// side_length - length of the polygon's side
// center - center point of circle with radius inradius
Polygon gen_poly(int circumradius, int vertices, int side_length, const Point& center);

// Returns third vertex of the triangle.
// a - first vertex of triangle
// b - second vertex of triangle
// d_ac - distance from a to c
// d_ab - distance from a to b
// d_bc - distance from b to c
std::pair<Graph_lib::Point, Graph_lib::Point> find_third_vertex(
	const Graph_lib::Point& a,
	const Graph_lib::Point& b,
	int d_ac,
	int d_ab,
	int d_bc
);

// Calculates side length of the N-sided polygon
// circumradius - circum circle's radius
// vertices - amount of angles/sides/vertices of the polygon
double calc_side_length(double circumradius, int vertices);
#endif // !REGULAR_POLYGON_HPP
