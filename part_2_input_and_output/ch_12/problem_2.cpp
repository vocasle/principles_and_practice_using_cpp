// Draws a rectangle with text inside

#include <graphics/Simple_window.h>

int main()
{
	using namespace Graph_lib;
	constexpr auto win_width = 800;
	constexpr auto win_height = 600;
	const auto p = Point{ 100, 100 };
	auto win = Simple_window{ p, win_width, win_height, "Exercise 2" };

	auto rect = Rectangle{ p, 100, 30 };
	auto text = Text{ Point{125, 120}, "Howdy!" };
	win.attach(rect);
	win.attach(text);
	win.wait_for_button();
}