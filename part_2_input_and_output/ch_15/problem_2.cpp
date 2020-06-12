#include <graphics/Window.h>
#include <graphics/Graph.h>
#include <functional>
#include <cmath>

typedef std::function<double(double)> func;

namespace gl = Graph_lib;

template <typename T>
class Fct : public gl::Shape
{
public:
	Fct(func f, double r1, double r2, gl::Point orig, T param, int count = 100, double xscale = 25, double yscale = 25) :
		m_func{ f }, m_r1{ r1 }, m_r2{ r2 }, m_orig{ orig }, m_param{ param }, m_count{ count }, m_xscale{ xscale }, m_yscale{ yscale }
	{
		if (r2 - r1 <= 0) error("bad graphing range");
		if (count <= 0) error("non-positive graphing count");
		update_points();
	}
	void reset()
	{
		m_func = nullptr;
		m_r1 = 0.0;
		m_r2 = 0.0;
		m_orig = gl::Point();
		m_count = 100;
		m_xscale = 25.0;
		m_yscale = 25.0;
		m_points.clear();
	}
	void draw_lines() const
	{
		if (color().visibility() && 1 < m_points.size())	// draw sole pixel?
			for (unsigned int i = 1; i < m_points.size(); ++i)
				fl_line(m_points[i - 1].x, m_points[i - 1].y, m_points[i].x, m_points[i].y);
	}
	void set_func(func fun) { m_func = fun; update_points(); }
	void set_range_from(double from) { m_r1 = from; update_points(); }
	void set_range_to(double to) { m_r2 = to; update_points(); }
	void set_origin(gl::Point orig) { m_orig = orig; update_points(); }
	void set_count(int count) { m_count = count; update_points(); }
	void set_xscale(double scale) { m_xscale = scale; update_points(); }
	void set_yscale(double scale) { m_yscale = scale; update_points(); }
private:
	func m_func;
	double m_r1;
	double m_r2;
	gl::Point m_orig;
	int m_count = 100;
	double m_xscale = 25.0;
	double m_yscale = 25.0;
	vector<gl::Point> m_points;
	T m_param;
	void update_points()
	{
		if (!m_points.empty())
			m_points.clear();
		if (m_r2 - m_r1 <= 0) error("bad graphing range");
		if (m_count <= 0) error("non-positive graphing count");
		double dist = (m_r2 - m_r1) / m_count;
		double r = m_r1;
		for (int i = 0; i < m_count; ++i) {
			m_points.emplace_back(m_orig.x + int(r * m_xscale), m_orig.y - int(m_func(r) * m_yscale));
			r += dist;
		}
	}
};

double parabola(double x)
{
	return x * x;
}

double hyperbola(double x)
{
	return x * x * x;
}

int main()
{
	gl::Window win = gl::Window({ 100, 100 }, 800, 600, "Exercise 2");
	Fct<int> fun = Fct<int>(parabola, -3.14, 3.14, gl::Point(400, 300), 100);
	fun.set_func(hyperbola);
	fun.set_range_from(-10.0);
	fun.set_range_to(11);
	fun.set_origin(gl::Point(200, 200));
	win.attach(fun);
	gl::gui_main();
}