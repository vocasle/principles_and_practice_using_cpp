
#include <graphics/Simple_window.h>

int main()
{
	auto win = Simple_window{ {100, 100}, 800, 600, "Exercise 11" };
	auto x_axis = Axis(Axis::Orientation::x, { 200, 300 }, 400);
	auto y_axis = Axis(Axis::Orientation::y, { 400, 450 }, 300);
	auto el = Ellipse(Point{ 400, 300 }, 150, 100);
	auto f1 = Mark(el.focus1(), '1');
	auto f2 = Mark(el.focus2(), '2');
	auto p = Point{ 99 + 400, 75 + 300 };
	auto l1 = Line(el.focus1(), p);
	auto l2 = Line(el.focus2(), p);
	win.attach(x_axis);
	win.attach(y_axis);
	win.attach(el);
	win.attach(f1);
	win.attach(f2);
	win.attach(l1);
	win.attach(l2);
	win.wait_for_button();
}