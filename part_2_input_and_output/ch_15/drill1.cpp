#include <graphics/Window.h>
#include <graphics/Graph.h>

double one(double) { return 1; }
double slope(double x) { return x / 2; }
double square(double x) { return x * x; }
double sloping_cos(double x) { return cos(x) + slope(x); }

int main()
{
	using namespace Graph_lib;
	constexpr unsigned int win_width = 600;
	Window win = Window(Point(100, 100), win_width, win_width, "Function graphs.");
	constexpr unsigned int axis_length = 400;
	Axis x_axis = Axis(Axis::Orientation::x, Point(100, 300), axis_length, axis_length / 20, "x axis");
	Axis y_axis = Axis(Axis::Orientation::y, Point(300, 500), axis_length, axis_length / 20, "y axis");
	x_axis.set_color(Color::red);
	y_axis.set_color(Color::red);
	win.attach(x_axis);
	win.attach(y_axis);

	const Point orig = Point(300, 300);
	constexpr double min = -10;
	constexpr double max = 11;
	constexpr int n = 400;
	constexpr double scale = 20;
	constexpr int font_size = 14;
	Function f1 = Function(one, min, max, orig, n, scale, scale);
	Function f2 = Function(slope, min, max, orig, n, scale, scale);
	Text f2_lbl = Text(Point(100, orig.y - int(slope(min) * scale) - font_size), "x/2");
	win.attach(f1);
	win.attach(f2);
	win.attach(f2_lbl);

	Function f3 = Function(square, min, max, orig, n, scale, scale);
	win.attach(f3);
	Function f4 = Function(cos, min, max, orig, n, scale, scale);
	f4.set_color(Color::blue);
	win.attach(f4);
	Function f5 = Function(sloping_cos, min, max, orig, n, scale, scale);
	win.attach(f5);
	gui_main();
}