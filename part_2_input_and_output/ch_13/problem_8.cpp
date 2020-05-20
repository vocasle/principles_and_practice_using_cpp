#include <graphics/Simple_window.h>
#include "Regular_hexagon.hpp"

int main()
{
	auto win = Simple_window{ {100, 100}, 800, 600, "Exercise 8" };
	auto hex = Regular_hexagon{ {400, 300}, 200 };
	win.attach(hex);
	win.wait_for_button();
}