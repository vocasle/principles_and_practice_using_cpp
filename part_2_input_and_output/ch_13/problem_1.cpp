#include <graphics/Simple_window.h>
#include "Arc.hpp"

int main()
{
	auto win = Simple_window{ Point{100, 100}, 800, 600, "Exercise 1" };
	const auto center = Point{ 400, 300 };
	auto arc = Arc{ center, 100, 90 };
	auto arc2 = Arc{ center, 150, 270 };
	auto arc3 = Arc{ center, 200, 180 };
	auto lbl = Text{ Point{center.x + 100, center.y}, std::to_string(arc.get_length()) };
	lbl.set_color(Color::red);
	auto lbl2 = Text{ Point{center.x + 150, center.y + 20}, std::to_string(arc2.get_length()) };
	auto lbl3 = Text{ Point{center.x + 200, center.y + 40}, std::to_string(arc3.get_length()) };
	lbl3.set_color(Color::yellow);
	arc.set_color(Color::red);
	arc3.set_color(Color::yellow);
	win.attach(arc);
	win.attach(arc2);
	win.attach(arc3);
	win.attach(lbl);
	win.attach(lbl2);
	win.attach(lbl3);
	win.wait_for_button();
}