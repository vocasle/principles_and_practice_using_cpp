// Draws a rectangle that is 3/4 the height of my screen and 2/3 the width inside the 1/4 inch frame

#include <graphics/Simple_window.h>

int main()
{
	using namespace Graph_lib;
	constexpr auto win_width = 800;
	constexpr auto win_height = 600;
	constexpr auto x = 100;
	constexpr auto y = 100;
	const auto p = Point{ x, y };
	auto win = Simple_window{ p, x_max(), y_max(), "Exercise 5" };
	// PPI of my screen is 157.35
	// 1 inch = 157.35
	auto margin = static_cast<int>(157.35 / 4);
	auto rect_height = static_cast<int>(y_max() * 3.0 / 4.0);
	auto rect_width = static_cast<int>(x_max() * 2.0 / 3.0);
	auto rect = Rectangle{ p, rect_width, rect_height };
	auto frame = Rectangle{ Point{p.x - margin, p.y - margin}, rect_width + margin * 2, rect_height + margin * 2 };
	frame.set_color(Color::red);
	
	win.attach(frame);
	win.attach(rect);
	win.wait_for_button();
}