#include <graphics/Simple_window.h>

vector<Point> points_on_circle(const Circle& c)
{
	static constexpr auto pi = 3.14159265;
	static constexpr auto n = 2 * pi / 100;
	auto points = vector<Point>();
	auto t = 0.0;
	while (t < 2 * pi)
	{
		auto x = c.center().x + c.radius() * cos(t);
		auto y = c.center().y + c.radius() * sin(t);
		points.emplace_back(x, y);
		t += n;
	}
	return points;
}

int main()
{
	auto win = Simple_window{ {100, 100}, 800, 600, "Exercise 12" };
	auto c = Circle({ 400, 300 }, 100);
	auto m = Mark({ 500, 300 }, 'X');
	auto points = points_on_circle(c);
	win.attach(c);
	win.attach(m);
	win.wait_for_button();
	
	for (auto& p : points)
	{
		auto dx = p.x - m.point(0).x;
		auto dy = p.y - m.point(0).y;
		m.move(dx, dy);
		win.wait_for_button();
	}
}