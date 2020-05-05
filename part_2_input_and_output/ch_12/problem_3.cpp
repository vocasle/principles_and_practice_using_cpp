// Draws my initials inside the window

#include <graphics/Simple_window.h>

int main()
{
	using namespace Graph_lib;
	constexpr auto win_width = 800;
	constexpr auto win_height = 600;
	const auto p = Point{ 100, 100 };
	auto win = Simple_window{ p, win_width, win_height, "Exercise 3" };
	auto name = Text{ p, "N" };
	name.set_color(Color::magenta);
	name.set_font(Font::courier_bold);
	name.set_font_size(150);
	auto lname = Text{ Point{200, 100}, "E" };
	lname.set_font(Font::courier_bold);
	lname.set_font_size(150);
	lname.set_color(Color::cyan);
	win.attach(name);
	win.attach(lname);
	win.wait_for_button();
}