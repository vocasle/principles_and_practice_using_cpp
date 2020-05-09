// Draws a house seen from the front

#include <graphics/Simple_window.h>

int main()
{
	auto win = Simple_window{ Point{100, 100}, 800, 600, "Exercise 7" };
	auto base = Rectangle{ Point{100, 300}, 400, 200 };
	auto roof = Polygon{};
	roof.add(Point{ 100, 300 });
	roof.add(Point{ 300, 100 });
	roof.add(Point({ 500, 300 }));
	auto roof_door = Rectangle{ Point{270, 180}, 60, 80 };
	auto l_win = Rectangle{ Point{170, 350}, 80, 80 };
	auto r_win = Rectangle{ Point{350, 350}, 80, 80 };
	auto chimney = Polygon{};
	chimney.add(Point{ 120, 300 });
	chimney.add(Point{ 120, 200 });
	chimney.add(Point{ 140, 200 });
	chimney.add(Point{ 140, 300 });
	chimney.set_fill_color(Color::white);
	roof.set_fill_color(Color::dark_green);
	roof_door.set_fill_color(Color::white);
	base.set_fill_color(Color::yellow);
	l_win.set_fill_color(Color::white);
	r_win.set_fill_color(Color::white);
	win.attach(base);
	win.attach(chimney);
	win.attach(roof);
	win.attach(roof_door);
	win.attach(l_win);
	win.attach(r_win);
	win.wait_for_button();
}