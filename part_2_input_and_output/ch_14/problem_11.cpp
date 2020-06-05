#include <graphics/Simple_window.h>
#include "Binary_tree.hpp"

int main()
{
	try
	{
		auto win = Simple_window{ {100, 100}, 800, 600, "Exercise 11" };
		auto bt = Binary_tree(6, { 100, 300 });
		bt.set_fill_color(Color::yellow);
		bt.set_color(Color::blue);
		win.attach(bt);
		win.wait_for_button();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unexpected exception\n";
		return 2;
	}
}