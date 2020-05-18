#ifndef ARROW_HPP
#define ARROW_HPP

#include <graphics/Graph.h>

class Arrow : public Graph_lib::Open_polyline
{
public:
	Arrow(Graph_lib::Point begin, Graph_lib::Point end);
	void draw_lines() const;
	void set_color(Graph_lib::Color col);
	void set_fill_color(Graph_lib::Color col);
private:
	Graph_lib::Polygon m_triangle;
};

int length_between(Graph_lib::Point begin, Graph_lib::Point end);

Graph_lib::Polygon create_triangle(Graph_lib::Point begin, Graph_lib::Point end);

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

#endif // !ARROW_HPP
