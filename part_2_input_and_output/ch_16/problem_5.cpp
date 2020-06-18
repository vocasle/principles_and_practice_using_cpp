#include <graphics/Window.h>
#include <graphics/GUI.h>

using namespace Graph_lib;

istream& operator>>(istream& is, Point& p);

class MyWindow : public Window
{
public:
	MyWindow(Point xy, int w, int h, const string& label)
		: Window(xy, w, h, label),
		button(Point(0, 0), 100, 20, "Move", [](Address, Address pw) {
		reference_to<MyWindow>(pw).move();
			})
	{
		attach(button);
	}

private:
	Button button;
	void move();
	Point get_point();
};

int main()
try
{
	MyWindow win{ {100, 100}, 800, 600, "Exercise 5" };
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

void MyWindow::move()
{
	Point p = get_point();
	button.move(p.x, p.y);
}

Point MyWindow::get_point()
{
	Point p;
	cin >> p;
	return p;
}

istream& operator>>(istream& is, Point& p)
{
	char ch1 = 0;
	char ch2 = 0;
	char ch3 = 0;
	Point pp;
	if (is >> ch1 >> pp.x >> ch2 >> pp.y >> ch3)
	{
		if (ch1 != '(' || ch2 != ',' || ch3 != ')')
		{
			is.clear(ios::failbit);
			return is;
		}
	}
	else
		return is;
	p = pp;
	return is;
}