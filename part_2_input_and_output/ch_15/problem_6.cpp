#include <graphics/Window.h>
#include "Bar.hpp"

int main()
{
	using namespace Graph_lib;
	constexpr int width = 800;
	constexpr int height = 600;
	const Point orig = Point(width / 2, height / 2);
	Window win = Window(orig, width, height, "Exercise 6");

	Bar bar = Bar(orig, { 1,2,3,4,5,6,7,8,9,10 });
	win.attach(bar);

	for (size_t i = 0; i < bar.num_of_bars(); ++i)
	{
		bar.set_fill_color(i, i);
		bar.set_label(i, "bar No. " + to_string(i), i);
	}

	bar.set_label("Bar graph example", Color::white);


	gui_main();
}