#include <graphics/Window.h>
#include <graphics/GUI.h>
#include <thread>

using namespace Graph_lib;

class Clock : public Circle
{
public:
	Clock(Point c, int r)
		: Circle(c, r) {
		generate_lines();
		Circle::set_color(Color::white);
		Circle::set_fill_color(Color::black);
	}
	void draw_lines() const;
	void update_second(Point end);
private:
	vector<Line> lines;
	void generate_lines();
};

class MyWindow : public Window
{
public:
	MyWindow(Point xy, int w, int h, const string& label)
		: Window(xy, w, h, label),
		c({ w / 2, h / 2 }, min(w / 2, h / 2)) {
		attach(c);
	}
	void update_clocks(Point s);
private:
	Clock c;
};

void loop(MyWindow& w);

int main()
try
{
	MyWindow win{ {100, 100}, 800, 600, "Exercise 6" };
	thread t(&loop, ref(win));
	return gui_main();
}
catch (exception& e)
{
	cerr << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "Unhandled exception\n";
	return 2;
}

void Clock::draw_lines() const
{
	Circle::draw_lines();
	for (auto line : lines)
		line.draw();	
}

void Clock::update_second(Point end)
{
	for (auto it = lines.begin(); it < lines.end(); ++it)
	{
		if (it->point(0) == end || it->point(1) == end)
			it->set_color(Color::white);
		else
			it->set_color(Color::black);
	}
}

void Clock::generate_lines()
{
	static constexpr double pi = 3.14159265;
	static constexpr double interval = 2 * pi / 60;
	
	for (double n = -pi/2 + interval; n < 3 * pi / 2; n += interval)
	{
		int x = center().x + radius() * cos(n);
		int y = center().y + radius() * sin(n);
		lines.push_back(Line(center(), { x,y }));
		lines[lines.size() - 1].set_color(Color::invisible);
	}
}

void loop(MyWindow& w)
{
	static constexpr double pi = 3.14159265;
	static constexpr double interval = 2 * pi / 60;
	for (double n = -pi / 2; ; n += interval)
	{
		_sleep(1000);
		if (n > 3 * pi / 2)
			n = -pi / 2;
		int x = w.x_max() / 2 + min(w.x_max() / 2, w.y_max() / 2) * cos(n);
		int y = w.y_max() / 2 + min(w.x_max() / 2, w.y_max() / 2) * sin(n);
		w.update_clocks({ x,y });
	}
}

void MyWindow::update_clocks(Point s)
{
	c.update_second(s);
	c.draw_lines();
}
