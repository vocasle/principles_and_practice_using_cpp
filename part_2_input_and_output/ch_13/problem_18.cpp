#include "Poly.hpp"
#include <graphics/Simple_window.h>

int main()
{
	auto win = Simple_window(Point(100, 100), 800, 600, "Exercise 18");
	auto poly = Poly({ {100, 200}, {200, 300}, {400, 500} });
	win.attach(poly);
	win.wait_for_button();
}