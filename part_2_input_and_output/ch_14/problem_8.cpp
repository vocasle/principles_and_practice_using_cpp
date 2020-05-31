#include <graphics/Simple_window.h>

class Octagon : public Polygon
{
public:
	Octagon(Point c, int circumradius) : Polygon()
	{
		static constexpr auto pi = 3.14159265;
		for (auto t = 0.0; t < 2 * pi; t += pi / 4)
		{
			auto x = static_cast<int>(c.x + circumradius * cos(t));
			auto y = static_cast<int>(c.y + circumradius * sin(t));
			Polygon::add({ x, y });
		}
	}
	void add(Point p) {} // does nothing
};



int main()
{
	auto win = Simple_window({ 100, 100 }, 800, 600, "Exercise 8");
	auto octagon = Octagon({ 400, 300 }, 100);
	octagon.set_style(Line_style::dash);
	octagon.set_color(Color::red);
	octagon.set_fill_color(Color::yellow);
	octagon.add({ 300, 400 });
	octagon.move(100, 100);
	win.attach(octagon);
	win.wait_for_button();
}