// Draws two rectangles inside a window.

#include <graphics/Simple_window.h>

int main()
{
	using namespace Graph_lib;
	constexpr auto window_width = 800;
	constexpr auto window_hight = 600;
	auto win = Simple_window{ Point{100, 100}, window_width, window_hight, "Exercise 1" };
	auto rect = Rectangle{ Point{100, 100}, 100, 50 };
	rect.set_color(Color::blue);
	auto poly = Polygon{};
	poly.set_color(Color::red);
	// Order of points matter!
	poly.add(Point{ 200, 200 });
	poly.add(Point{ 200, 250 });
	poly.add(Point{ 300, 250 });
	poly.add(Point{ 300, 200 });
	win.attach(rect);
	win.attach(poly);
	win.wait_for_button();
}