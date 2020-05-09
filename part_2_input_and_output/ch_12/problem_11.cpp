// This program draws a series of regular polygons.
// Path 1: All polygons will be drawn inside a circle. // this idea was busted before it was implemented.
// Equation of a circle
// (x - h)^2 + (y - k)^2 = r^2, where (h, k) - center of the circle, r - radius of the circle.
//
// Path 2: All polygons will be drawn in following order:
// We draw a circle with radius r. We draw a regular rectangle around this circle, so that all edges of rectangle
// will touch the circle. We draw a circle around rectangle, let's call this circle C. Around circle C we draw a square.
// Around this square we draw another circle C1. Around C1 we draw a pentagon. And so on.
// 
// This idea arised after reading arcticle: https://mathworld.wolfram.com/RegularPolygon.html
// 
// find_third_vertex() uses solution from thread:
// https://math.stackexchange.com/a/3021334/677156
//
// It turned out, that what I have implemented in Path 2 is called Polygon Circumscribing.
// You can read a
// https://mathworld.wolfram.com/PolygonCircumscribing.html


#include <graphics/Simple_window.h>
#include <cassert>


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

double calc_circumradius(int inner_circle_rad, int vertices);

// Generates N-sided polygon
// inradius - radius of incircle
// vertices - number of sides/vertices/angles
// side_length - length of the polygon's side
// center - center point of circle with radius inradius
Graph_lib::Polygon gen_poly(int inner_circle_rad, int vertices, int side_length, const Graph_lib::Point& center)
{
	using namespace Graph_lib;
	auto R = static_cast<int>(calc_circumradius(inner_circle_rad, vertices)); // Radius of outer circle
	auto points = vector<Point>();
	auto p = Point{ center.x, center.y + R }; // Starting point.
	for (auto i = 0; i < vertices; ++i)
	{
		auto [v1, v2] = find_third_vertex(p, center, R, side_length, R);
		if (find(points.begin(), points.end(), v1) == points.end())
		{
			points.push_back(v1);
			p = v1;
		}
		else if (find(points.begin(), points.end(), v2) == points.end())
		{
			points.push_back(v2);
			p = v2;
		}
		else
		{
			error("Duplicate point.");
		}
	}
	auto poly = Polygon{};
	for (auto& point : points)
	{
		poly.add(point);
	}
	return poly;
}

// Calculates secant
// angle - an angle in radians
double secant(double angle)
{
	return 1 / cos(angle);
}

// Calculates radius of the circumscribed circle of the N-sided polygon
// inradius - incircle radius of the N-sided polygon
// vertices - amount of angles/sides/vertices of the polygon
double calc_circumradius(int inradius, int vertices)
{
	static constexpr auto pi = 3.14159265;
	return inradius * secant(pi / vertices);
}

// Calculates side length of the N-sided polygon
// circumradius - circum circle's radius
// vertices - amount of angles/sides/vertices of the polygon
double calc_side_length(double circumradius, int vertices)
{
	static constexpr auto pi = 3.14159265;
	return 2 * circumradius * sin(pi / vertices);
}

int main()
{
	using namespace Graph_lib;
	constexpr auto pi = 3.14159265;
	constexpr auto win_width = 800, win_height = 600;
	auto win = Simple_window{ Point{100, 100}, win_width, win_height, "Exercise 11" };
	const auto center = Point{ win_width / 2, win_height / 2 };

	auto radius = 40;
	auto polygons = vector<Polygon>();
	auto color_cnt = 0;
	for (auto vertices = 3; vertices < 50; ++vertices)
	{
		auto circumradius = calc_circumradius(radius, vertices);
		auto side_length = calc_side_length(circumradius, vertices);
		auto poly = gen_poly(radius, vertices, side_length, center);
		polygons.push_back(poly);
		radius = circumradius;
	}
	for (auto& poly : polygons)
	{
		win.attach(poly);
	}
	win.wait_for_button();
}