#include <graphics/Window.h>
#include <graphics/GUI.h>
#include <graphics/Graph.h>

using namespace Graph_lib;

class Grid : public Shape
{
public:
	Grid(Point tl, int w, int h, int grid_size = 10) : Shape(), grid_size{ grid_size }, orig{ tl.x + w / 2, tl.y + h / 2 }, xscale{ w / grid_size }, yscale{ h / grid_size } {
		for (int n = 0; n <= w; n += w / grid_size)
			ver.add({ tl.x + n, tl.y }, { tl.x + n, tl.y + h });
		for (int n = 0; n <= h; n += h / grid_size)
			hor.add({ tl.x, tl.y + n }, { tl.x + w, tl.y + n });
		hor.set_color(Color::black);
		ver.set_color(Color::black);
	}
	void draw_lines() const;
	void set_color(Color c);
	int get_grid_size() const { return grid_size; }
	Point get_orig() const { return orig; }
	int get_yscale() const { return yscale; }
	int get_xscale() const { return xscale; }
private:
	Lines ver;
	Lines hor;
	int xscale;
	int yscale;
	const int grid_size;
	const Point orig;
};

class MyWindow : public Window
{
public:
	MyWindow(Point xy, int w, int h, const string& label)
		: Window(xy, w, h, label),
		menu{{x_max() - 80, 10}, 70, 20, Menu::vertical, "functions"},
		grid{{100, 100}, x_max() - 200, y_max() - 200}
	{
		menu.attach(new Button{ {0,0},0,0,"sin", [](Address,Address pw) { reference_to<MyWindow>(pw).draw_sine(); } });
		menu.attach(new Button{ {0,0},0,0,"cos", [](Address,Address pw) { reference_to<MyWindow>(pw).draw_cosine(); } });
		menu.attach(new Button{ {0,0},0,0,"tan", [](Address,Address pw) { reference_to<MyWindow>(pw).draw_tangent(); } });
		menu.attach(new Button{ {0,0},0,0,"cot", [](Address,Address pw) { reference_to<MyWindow>(pw).draw_cotangent(); } });
		attach(menu);
		attach(grid);
	}
private:
	Menu menu;
	void draw_sine();
	void draw_cosine();
	void draw_tangent();
	void draw_cotangent();
	Function* f = nullptr;
	Grid grid;
};


int main()
try
{
	MyWindow win{ {100, 100}, 800, 600, "Exercise 10" };
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

void MyWindow::draw_sine()
{
	const int size = grid.get_grid_size() / 2;
	delete f;
	f = new Function([](double x) { return sin(x); }, -size, size, grid.get_orig(), 100, grid.get_xscale(), grid.get_yscale());
	attach(*f);
	redraw();
}

void MyWindow::draw_cosine()
{
	const int size = grid.get_grid_size() / 2;
	delete f;
	f = new Function([](double x) { return cos(x); }, -size, size, grid.get_orig(), 100, grid.get_xscale(), grid.get_yscale());
	attach(*f);
	redraw();
}

void MyWindow::draw_tangent()
{
	const int size = grid.get_grid_size() / 2;
	delete f;
	f = new Function([](double x) { return tan(x); }, -size, size, grid.get_orig(), 100, grid.get_xscale(), grid.get_yscale());
	attach(*f);
	redraw();
}

void MyWindow::draw_cotangent()
{
	const int size = grid.get_grid_size() / 2;
	delete f;
	f = new Function([](double x) { return 1 / tan(x); }, -size, size, grid.get_orig(), 100, grid.get_xscale(), grid.get_yscale());
	attach(*f);
	redraw();
}

void Grid::draw_lines() const
{
	ver.draw();
	hor.draw();
}

void Grid::set_color(Color c)
{
	ver.set_color(c);
	hor.set_color(c);
}
