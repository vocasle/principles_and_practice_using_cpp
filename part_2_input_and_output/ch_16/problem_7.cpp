#include <graphics/Window.h>
#include <graphics/GUI.h>

// Those 3 lines were added to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace Graph_lib;

struct Data
{
	Window* win;
	Image* img;
	Point* p;
};

class MyWindow : public Window
{
public:
	MyWindow(Point xy, int w, int h, const string& label)
		: Window(xy, w, h, label),
		start(Point(x_max() - 70, 0), 70, 20, "start", [](Address, Address pw) {
			reference_to<MyWindow>(pw).move_loop();
		}),
		stop(Point(x_max() - 70, 20), 70, 20, "stop", [](Address, Address pw) {
			Fl::remove_timeout(&MyWindow::move_image);
		}),
		img(Point(x_max() - 200, y_max() / 2), "problem_7.jpg")
	{
		attach(start);
		attach(stop);
		attach(img);
		generate_points();
	}

private:
	Button start;
	Button stop;
	Image img;
	vector<Point> points;
	void move_loop();
	void generate_points();
	static void move_image(void* data);
};


int main()
try
{
	// This line is added to print info about found memory leaks to Output window of Visual Studio
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	MyWindow win{ {100, 100}, 800, 600, "Exercise 7" };
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


void MyWindow::move_loop()
{
	for (auto it = points.begin(); it < points.end(); ++it)
	{
		Data* d = new Data();
		d->img = &img;
		d->p = &*it;
		d->win = this;
		Fl::add_timeout(double(it - points.begin()), &MyWindow::move_image, reinterpret_cast<void*>(d));
		redraw();
	}
}

void MyWindow::move_image(void* data)
{
	auto d = reinterpret_cast<Data*>(data);
	Point a = d->img->point(0);
	Point* b = d->p;
	d->img->move(b->x - a.x, b->y - a.y);
	d->win->redraw();
	delete d;
}

void MyWindow::generate_points()
{
	static constexpr double pi = 3.14159265;
	static constexpr double interval = 2 * pi / 60;
	static constexpr int img_height = 100;
	static int radius = min(x_max() / 2, y_max() / 2 - img_height);
	static const Point orig = Point(x_max() / 2, y_max() / 2);

	for (double n = interval; n < 2 * pi; n += interval)
	{
		int x = orig.x + radius * cos(n);
		int y = orig.y + radius * sin(n);
		points.push_back(Point(x, y));
	}
}