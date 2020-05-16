#include "Box.hpp"

#include <graphics/Simple_window.h>

int main()
{
	try
	{
		auto win = Simple_window{ Point{100, 100}, 800, 600, "Exercise 2" };
		auto box = Box{ Point{350, 250}, 300, 50 };
		box.set_color(Color::yellow);
		box.set_fill_color(Color::red);

		auto box2 = Box{ Point{0, 0}, 500, 50 };
		box2.set_color(Color::white);

		auto box3 = Box{ Point{100,100}, 100, 50 };
		box3.set_color(Color::red);
		box3.set_fill_color(Color::dark_green);
		win.attach(box);
		win.attach(box2);
		win.attach(box3);
		win.wait_for_button();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unexpected exception.\n";
		return 2;
	}
}