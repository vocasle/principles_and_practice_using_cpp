#include <graphics/Simple_window.h>
#include "Right_triangle.hpp"
#include "Regular_polygon.hpp"

bool is_in_circle(Point p, int radius, Point c)
{
	return radius * radius == (p.x - c.x) * (p.x - c.x) + (p.y - c.y) * (p.y - c.y);
}

int main()
{
	auto win = Simple_window({ 100, 100 }, 800, 600, "Exercise 14");
	auto octagon = Regular_polygon({ 400, 300 }, 100, 8);
	auto points = vector<Point>();
	for (auto i = 0; i < octagon.number_of_points(); ++i)
	{
		points.push_back(octagon.point(i));
	}
	points.push_back(octagon.point(0));
	auto triangles = vector<Right_triangle>();
	for (size_t i = 1; i < points.size(); ++i)
	{
		auto a = points.at(i - 1);
		auto b = points.at(i);
		auto d = Point((a.x + b.x) / 2, (a.y + b.y) / 2);
		auto d_ab = distance(a, b);
		auto d_db = distance(d, b);
		auto d_ac = sqrt(2 * d_db * d_db);
		auto [c1, c2] = find_third_vertex(a, b, d_ac, d_ac, d_ab);
		if (is_in_circle(c1, 100, { 400, 300 }))
		{
			triangles.push_back(Right_triangle(a, b, c1));
		}
		else
		{
			triangles.push_back(Right_triangle(a, b, c2));
		}
		triangles.at(triangles.size() - 1).set_fill_color(i);
	}
	for (auto& t : triangles)
	{
		win.attach(t);
	}
	win.wait_for_button();
}