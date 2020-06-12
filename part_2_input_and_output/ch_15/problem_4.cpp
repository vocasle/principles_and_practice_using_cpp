#include <graphics/Window.h>
#include <graphics/Graph.h>

int main()
{
	using namespace Graph_lib;
	constexpr int width = 800;
	constexpr int height = 600;
	const Point orig = Point(width / 2, height / 2);
	Window win = Window(orig, width, height, "Exercise 4");
	constexpr int from = -10;
	constexpr int to = 11;
	constexpr int scale = 25;
	constexpr int xlen = width - 40;
	constexpr int ylen = height - 40;
	Axis x = Axis(Axis::Orientation::x, { 20, orig.y }, xlen, xlen / scale, "X");
	x.set_color(Color::yellow);
	x.label.move(-200, 0);
	Axis y = Axis(Axis::Orientation::y, { orig.x, 580 }, ylen, ylen / scale, "Y");
	y.set_color(Color::yellow);
	win.attach(x);
	win.attach(y);
	Function fun1 = Function(sin, from, to, orig);
	fun1.set_color(Color::red);
	Function fun2 = Function(cos, from, to, orig);
	fun2.set_color(Color::blue);
	Function fun3 = Function([](double x) { return sin(x) + cos(x); }, from, to, orig);
	fun3.set_color(Color::cyan);
	Function fun4 = Function([](double x) {
		return sin(x) * sin(x) + cos(x) + cos(x);
		}, from, to, orig);
	fun4.set_color(Color::green);
	win.attach(fun1);
	win.attach(fun2);
	win.attach(fun3);
	win.attach(fun4);
	constexpr int margin = 20;
	Text t1 = Text({ orig.x + 100, orig.y - 200 }, "sin (x)");
	Text t2 = Text(t1.point(0), "cos (x)");
	Text t3 = Text(t1.point(0), "sin (x) + cos (x)");
	Text t4 = Text(t1.point(0), "sin (x) * sin (x) + cos (x) * cos (x)");
	t4.move(0, margin * 3);
	t4.set_color(Color::green);
	t3.move(0, margin * 2);
	t3.set_color(Color::cyan);
	t2.move(0, margin);
	t2.set_color(Color::blue);
	t1.set_color(Color::red);
	win.attach(t1);
	win.attach(t2);
	win.attach(t3);
	win.attach(t4);
	gui_main();
}