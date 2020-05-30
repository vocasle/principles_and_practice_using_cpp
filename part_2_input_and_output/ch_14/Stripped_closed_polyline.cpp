#include "Stripped_closed_polyline.hpp"

// The main idea is to draw a bounding rectangle around our polygon
// after that we start from top left corner of bounding rectangle and check
// each pixel if it is inside our shape
// if it is in our shape and fill color is assigned - we draw that pixel
// actually, we draw the line from first pixel inside the shape
// to the last pixel inside the shape with the same y coordinate
void Stripped_closed_polyline::draw_lines() const
{
	if (fill_color().visibility() && number_of_points() > 2)
	{
		fl_color(fill_color().as_int());
		// height of bounding rectangle
		auto height = y_max - y_min;
		// width of bounding rectangle
		auto width = x_max - x_min;
		// all edges of the shape
		auto edges = get_edges();
		// holds points that are inside of our shape
		auto pts = vector<Point>();
		// start from first row 
		for (auto i = 0; i < height; i += 2)
		{
			// start from first column
			for (auto j = 0; j < width; ++j)
			{
				auto p = Point(x_min + j, y_min + i);
				if (includes(p, edges))
					pts.push_back(p);
			}
			if (pts.size() > 1)
				fl_line(pts[0].x, pts[0].y, pts[pts.size() - 1].x, pts[pts.size() - 1].y);
			pts.clear();
		}
		fl_color(color().as_int());	// reset color
	}
}

void Stripped_closed_polyline::add(Point p)
{
	Closed_polyline::add(p);
	recalc_bounding_rect();
}

void Stripped_closed_polyline::recalc_bounding_rect()
{
	if (number_of_points() < 3)
		return;

	for (auto i = 0; i < number_of_points(); ++i)
	{
		if (point(i).x > x_max)
			x_max = point(i).x;
		if (point(i).x < x_min)
			x_min = point(i).x;
		if (point(i).y > y_max)
			y_max = point(i).y;
		if (point(i).y < y_min)
			y_min = point(i).y;
	}
}

vector<Line> Stripped_closed_polyline::get_edges() const
{
	auto lines = vector<Line>();
	for (auto i = 0; i < number_of_points(); ++i)
	{
		auto next = i + 1 == number_of_points() ? 0 : i + 1;
		lines.emplace_back(point(i), point(next));
	}
	return lines;
}

// includes was implemented by rewriting Python function includes() on this page
// http://philliplemons.com/posts/ray-casting-algorithm
bool includes(const Point& p, const vector<Line>& edges)
{
	auto py = p.y;
	// We start on the outside of the polygon
	auto isInside = false;
	//  is used to make sure points are not on the same line as vertexes
	auto eps = 0.00001;
	for (auto& edge : edges)
	{
		auto a = edge.point(0);
		auto b = edge.point(1);
		// Make sure A is the lower point of the edge
		if (a.y > b.y)
		{
			auto c = a;
			a = b;
			b = c;
		}
		// Make sure point is not at same height as vertex
		if (py == a.y || py == b.y)
			py += eps;
		if (py > b.y || py < a.y || p.x > max(a.x, b.x))
			// The horizontal ray does not intersect with the edge
			continue;
		if (p.x <= min(a.x, b.x))
		{
			// The ray intersects with the edge
			isInside = !isInside;
			continue;
		}
		auto m_edge = INFINITY;
		auto m_point = INFINITY;
		if (b.x - a.x != 0)
			m_edge = double(b.y - a.y) / double(b.x - a.x);
		if (p.x - a.x != 0)
			m_point = double(py - a.y) / double(p.x - a.x);
		if (m_point >= m_edge)
			isInside = !isInside;
	}
	return isInside;
}
