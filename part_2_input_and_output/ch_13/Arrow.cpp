#include "Arrow.hpp"

using namespace Graph_lib;

Arrow::Arrow(Point begin, Point end) : m_triangle{create_triangle(begin, end)}
{
	add(begin);
	add(end);
	m_triangle.set_fill_color(Color::black);
	m_triangle.set_color(Color::black);
}

void Arrow::draw_lines() const
{
	Open_polyline::draw_lines();
	m_triangle.draw_lines();
}

void Arrow::set_color(Color col)
{
	Open_polyline::set_color(col);
	m_triangle.set_color(col);
}

void Arrow::set_fill_color(Color col)
{
	Open_polyline::set_fill_color(col);
	m_triangle.set_fill_color(col);
}

Graph_lib::Polygon create_triangle(Graph_lib::Point begin, Graph_lib::Point end)
{
	auto triangle = Polygon();
	static constexpr const auto pi = 3.14159265;
	static constexpr const auto alpha = pi / 6;
	static constexpr const auto length = 10;
	auto l1 = length_between(begin, end);
	// vector from begin to end
	auto vec = Point{ end.x - begin.x, end.y - begin.y };
	// unit vector in direction of v
	auto u_x = double(vec.x) / l1;
	auto u_y = double(vec.y) / l1;
	// middle point
	auto middle = Point{ static_cast<int>(end.x - u_x * length), static_cast<int>(end.y - u_y * length) };
	auto d_ab = length_between(middle, end);
	// a - is end, d_ac - length from a to c, where c - is third point
	auto d_ac = static_cast<int>(d_ab / cos(alpha));
	// b - is middle, d_bc - length from b to c
	auto d_bc = static_cast<int>(d_ac * sin(alpha));
	auto [left, right] = find_third_vertex(end, middle, d_ac, d_ab, d_bc);
	triangle.add(end);
	triangle.add(left);
	triangle.add(right);
	return triangle;
}

int length_between(Graph_lib::Point begin, Graph_lib::Point end)
{
	return static_cast<int>(sqrt(pow(end.x - begin.x, 2) + pow(end.y - begin.y, 2)));
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
