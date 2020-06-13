#include <graphics/Simple_window.h>

double leibniz_series(double n)
{
	double sum = 0.0;
	for (size_t i = 0; i < n; ++i)
		sum += 2.0 / ((4 * i + 1) * (4 * i + 3));
	return sum;
}


int main()
{
	constexpr int xmax = 800;
	constexpr int ymax = 600;
	Simple_window win = Simple_window({ 100, 100 }, xmax, ymax, "Exercise 5");
	constexpr int r_min = -100;
	constexpr int r_max = 101;
	constexpr int x_scale = 30;
	constexpr int y_scale = 30;
	const Point orig = Point(xmax / 2, ymax / 2);
	Axis oy = Axis(Axis::Orientation::y, { orig.x, orig.y + ymax / 2 - 20 }, ymax - 40, (ymax - 40) / y_scale, "y");
	win.attach(oy);
	for (int n = 0; n < 50; ++n)
	{
		ostringstream oss;
		oss << "pi / 4 approximation; n==" << n;
		win.set_label(oss.str());
		Function f = Function(leibniz_series, r_min, r_max, orig, 200, x_scale, y_scale);
		win.attach(f);
		win.wait_for_button();
		win.detach(f);
	}
}