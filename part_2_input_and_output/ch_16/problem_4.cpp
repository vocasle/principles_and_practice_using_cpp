#include <graphics/Window.h>
#include <graphics/GUI.h>
#include "../ch_13/Regular_polygon.hpp"

using namespace Graph_lib;

class MyWindow : public Window
{
public:
	MyWindow(Point xy, int w, int h, const string& label)
		: Window(xy, w, h, label),
		menu(Point(x_max() - 70, 0), 70, 20, Menu::vertical, "shapes"),
		x_in(Point(x_max() - 220, 0), 50, 20, "x:"),
		y_in(Point(x_max() - 140, 0), 50, 20, "y:"),
		poly{nullptr}
	{
		menu.attach(new Button(Point(0, 0), 0, 0, "circle", [](Address, Address pw) {
			reference_to<MyWindow>(pw).create_circle();
		}));
		menu.attach(new Button(Point(0, 0), 0, 0, "square", [](Address, Address pw) {
			reference_to<MyWindow>(pw).create_square();
		}));
		menu.attach(new Button(Point(0, 0), 0, 0, "triangle", [](Address, Address pw) {
			reference_to<MyWindow>(pw).create_triangle();
		}));
		menu.attach(new Button(Point(0, 0), 0, 0, "hexagon", [](Address, Address pw) {
			reference_to<MyWindow>(pw).create_hexagon();
		}));
		attach(menu);
		attach(x_in);
		attach(y_in);
	}

private:
	Menu menu;
	In_box x_in;
	In_box y_in;
	Regular_polygon* poly;

	void create_circle();
	void create_square();
	void create_triangle();
	void create_hexagon();
	void create_shape(int n);
	Point get_point();
	int get_circumradius(Point p) const;
};

int main()
try
{
	MyWindow win{ {100, 100}, 800, 600, "Exercise 4" };
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

void MyWindow::create_circle()
{
	create_shape(20);
}

void MyWindow::create_square()
{
	create_shape(4);
}

void MyWindow::create_triangle()
{
	create_shape(3);
}

void MyWindow::create_hexagon()
{
	create_shape(6);
}

void MyWindow::create_shape(int n)
{
	Point c = get_point();
	int circumradius = get_circumradius(c);
	detach(*poly);
	delete poly;
	poly = new Regular_polygon(c, circumradius, n);
	attach(*poly);
	redraw();
}

Point MyWindow::get_point()
{
	int x = x_in.get_int();
	int y = y_in.get_int();
	return Point(x, y);
}

int MyWindow::get_circumradius(Point p) const
{
	return min(p.x, p.y) / 2;
}
