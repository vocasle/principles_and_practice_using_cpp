#include <graphics/Simple_window.h>
#include "Arrow.hpp"

int main()
{
	auto win = Simple_window{ Point{100, 100}, 800, 600, "Exercise 3" };
	auto arrow = Arrow({ 100, 100 }, { 200, 100 });
	auto a2 = Arrow{ {100, 100}, {400, 400} };
	auto a3 = Arrow{ {400, 200}, {400, 500} };
	a3.set_fill_color(Color::green);
	auto a4 = Arrow{ {400, 200}, {400, 201} };
	win.attach(arrow);
	win.attach(a2);
	win.attach(a3);
	win.attach(a4);
	win.wait_for_button();
}

