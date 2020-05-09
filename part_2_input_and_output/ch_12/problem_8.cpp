// Draws olympic rings

#include <graphics/Simple_window.h>

int main()
{
	auto win = Simple_window{ Point{100, 100}, 800, 600, "Exercise 8" };
	const auto style = Line_style{ Line_style::solid, 10 };
	auto circle1 = Circle{ Point{200, 200}, 100 };
	auto circle2 = Circle{ Point{310, 300}, 100 };
	auto circle3 = Circle{ Point{420, 200}, 100 };
	auto circle4 = Circle{ Point{530, 300}, 100 };
	auto circle5 = Circle{ Point{640, 200}, 100 };
	circle1.set_style(style);
	circle1.set_color(Color::blue);
	circle2.set_style(style);
	circle2.set_color(Color::yellow);
	circle3.set_style(style);
	circle4.set_style(style);
	circle4.set_color(Color::green);
	circle5.set_style(style);
	circle5.set_color(Color::red);
	win.attach(circle1);
	win.attach(circle2);
	win.attach(circle3);
	win.attach(circle4);
	win.attach(circle5);
	win.wait_for_button();
}