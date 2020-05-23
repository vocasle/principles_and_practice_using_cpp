#include <graphics/Simple_window.h>
#include "Regular_polygon.hpp"

int main()
{
	static constexpr auto win_width = 800;
	static constexpr auto win_height = 600;
	auto win = Simple_window({ 100, 100 }, win_width, win_height, "Exercise 15");
	static constexpr auto circumradius = 50;
	static constexpr auto pi = 3.14159265;
	auto hexagons = vector<Regular_polygon>();
	for (auto i = 0; i < 7; ++i)
	{
		for (auto j = 0; j < 9; ++j)
		{
			auto a = Point(j * 100, i * 100);
			if (j % 2 == 0)
			{
				a.y += circumradius;
			}
			hexagons.push_back(Regular_polygon(a, circumradius, 6));
			hexagons.at(hexagons.size() - 1).set_fill_color(i + j);
		}
	}

	for (auto& hex : hexagons)
	{
		win.attach(hex);
	}
	win.wait_for_button();
}