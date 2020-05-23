#include <graphics/Simple_window.h>
#include "Right_triangle.hpp"

int main()
{
	static constexpr auto win_width = 800;
	static constexpr auto win_height = 600;
	auto win = Simple_window({ 100, 100 }, win_width, win_height, "Exercise 15");
	auto triangles = vector<Right_triangle>();
	for (auto i = 0; i < 6; ++i)
	{
		for (auto j = 0; j < 8; ++j)
		{
			auto a = Point(j * 100, i * 100);
			auto b = Point(a.x, a.y + 100);
			auto c = Point(b.x + 100, b.y);
			triangles.push_back(Right_triangle(a, b, c));
		}
	}

	for (auto& t : triangles)
	{
		win.attach(t);
	}
	win.wait_for_button();
}