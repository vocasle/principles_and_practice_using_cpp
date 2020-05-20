#include "Regular_hexagon.hpp"
#include <graphics/Simple_window.h>

int main()
{
	auto win = Simple_window{ {100, 100}, 800, 600, "Exercise 9" };
	auto hexs = vector<Regular_hexagon>();
	for (auto i = 1; i < 5; ++i)
	{
		for (auto j = 1; j < 5; ++j)
		{
			hexs.emplace_back(Point{ j * 100, 100 * i }, 50);
		}
	}
	for (auto& hex : hexs)
	{
		win.attach(hex);
	}
	win.wait_for_button();
}