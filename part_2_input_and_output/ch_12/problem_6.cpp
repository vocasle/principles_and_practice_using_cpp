// This program draws two windows.
// First window contains a rectangle that is bigger than window. In this case parts of rectangle that won't fit
// into window will not show outside the window.
//
// Second window is bigger than the screen. In this case the window will spread below the screen. In another words,
// if screen was resizable, we could see, that window will be as big as you want.

#include <graphics/Simple_window.h>

int main()
{
	using namespace Graph_lib;
	constexpr auto win_width = 800;
	constexpr auto win_height = 600;
	constexpr auto x = 100;
	constexpr auto y = 100;
	const auto p = Point{ x, y };
	auto win = Simple_window{ p, win_width, win_height, "Exercise 6 - Rectangle won't fit into window" };
	auto rect = Rectangle{ p, x_max() * 2, y_max() * 2 }; // won't fit inside the window
	win.attach(rect);

	auto win2 = Simple_window{ p, win_width * 10, win_height * 10, "Exercise 6 - Window is bigger that screen" };	
	win.wait_for_button();
	win2.wait_for_button();
}