#include <graphics/Simple_window.h>
#include "Star.hpp"

int main()
{
	try
	{
		auto win = Simple_window(Point(100, 100), 800, 600, "Exercise 19");
		auto c = Point(400, 300);
		auto star = Star(c, 200, 13, 5);
		win.attach(star);
		win.wait_for_button();
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "Unexpected exception occured.\n";
		return 2;
	}
}