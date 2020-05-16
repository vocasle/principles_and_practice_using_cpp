#include "Box.hpp"

Box::Box(Graph_lib::Point top_left, int side_length, int corner_radius, unsigned int span)
	: m_top_left{ top_left }, m_side_length{ side_length }, m_corner_radius{ corner_radius }, m_span{span}
{
	if (side_length == 0 || side_length < 0)
	{
		error("Negative side length or it is equal to zero.");
	}
	if (corner_radius > side_length / 2 || corner_radius < 0)
	{
		error("Corner radius greater than half of the side length or is negative.");
	}
	auto points = generate_guide_line_points(top_left, side_length, corner_radius, span);
	for (auto& point : points)
	{
		add(point);
	}
}

vector<Graph_lib::Point> generate_guide_line_points(Graph_lib::Point top_left, int side_length, int corner_radius, unsigned int span)
{
	static constexpr const auto pi = 3.14159265;
	using namespace Graph_lib;
	auto points = vector<Point>();
	auto tl = Point{ top_left.x + corner_radius, top_left.y + corner_radius };
	auto tr = Point{ tl.x + side_length - 2 * corner_radius, tl.y };
	auto br = Point{ tr.x, tr.y + side_length - 2 * corner_radius };
	auto bl = Point{ tl.x, br.y };
	auto arc_tl = get_arc_points(tl, corner_radius, pi, 3 * pi / 2, span);
	auto arc_tr = get_arc_points(tr, corner_radius, 3 * pi / 2, 2 * pi, span);
	auto arc_br = get_arc_points(br, corner_radius, 0, pi / 2, span);
	auto arc_bl = get_arc_points(bl, corner_radius, pi / 2, pi, span);
	points.insert(points.end(), arc_tl.begin(), arc_tl.end());
	points.insert(points.end(), arc_tr.begin(), arc_tr.end());
	points.insert(points.end(), arc_br.begin(), arc_br.end());
	points.insert(points.end(), arc_bl.begin(), arc_bl.end());
	return points;
}

vector<Graph_lib::Point> get_arc_points(Graph_lib::Point center, int radius, double start, double end, unsigned int span)
{
	auto points = vector<Graph_lib::Point>();
	for (auto t = start; t < end; t += (end - start) / span)
	{
		auto x = double(center.x) + double(radius) * cos(t);
		auto y = double(center.y) + double(radius) * sin(t);
		points.emplace_back(static_cast<int>(x), static_cast<int>(y));
	}
	return points;
}
