#include <graphics/Simple_window.h>
#include "Stripped_closed_polyline.hpp"


int main()
{
	auto win = Simple_window(Point(100, 100), 800, 600, "Exercise 7");
	auto pl = Stripped_closed_polyline();
	pl.add({ 100, 100 });
	pl.add({ 200, 123 });
	pl.add({ 250, 100 });
	pl.add({ 300, 200 });
	pl.add({ 150, 150 });
	pl.add({ 150, 300 });
	pl.set_fill_color(Color::yellow);
	win.attach(pl);
	win.wait_for_button();
}