#include "Regular_hexagon.hpp"
#include <graphics/Simple_window.h>

int main()
{
	auto win = Simple_window{ {100, 100}, 800, 600, "Exercise 9" };
	auto hexs = vector<Regular_hexagon>();
	constexpr auto circumradius = 50;
	static constexpr auto pi = 3.14159;
	static const auto inradius = static_cast<int>(circumradius * cos(pi / 6));
	static const auto side_length = static_cast<int>(2 * circumradius * sin(pi / 6));
	
	auto y = 200;
	for (auto i = 0; i < 4; ++i)
	{
		auto x = 100 + i * (circumradius * 2 + side_length);
		for (auto j = 0; j < 3; ++j)
		{
			switch (j)
			{
			case 1:
				x += circumradius + side_length / 2;
				y -= inradius;
				break;
			case 2:
				y += inradius * 2;
				break;
			default:
				y -= inradius;
				break;
			}

			hexs.emplace_back(Point{ x, y }, circumradius);
		}
	}
	for (auto& hex : hexs)
	{
		win.attach(hex);
	}
	win.wait_for_button();
}