#include <graphics/Window.h>
#include <graphics/GUI.h>

using namespace Graph_lib;

inline int rand_int(int min, int max)
{
	static default_random_engine ran;
	return uniform_int_distribution<>{min, max}(ran);
}

class MyWindow : public Window
{
public:
	MyWindow(Point xy, int w, int h, const string& label)
		: Window(xy, w, h, label),
		image(Point(0,0), "problem_3.jpg"),
		button(Point(0, 100), 100, 20, "Move", [](Address, Address pw) {
			reference_to<MyWindow>(pw).move();
		})
	{
		attach(image);
		attach(button);
	}

private:
	Image image;
	Button button;
	void move();
};

int main()
try
{
	MyWindow win{ {100, 100}, 800, 600, "Exercise 3" };
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
	constexpr int width = 100;
	constexpr int height = 120;
	static int xmax = x_max() - width;
	static int ymax = y_max() - height;
	int old_x = image.point(0).x;
	int old_y = image.point(0).y;
	int x = rand_int(0, xmax);
	int y = rand_int(0, ymax);
	if (old_x + x >= xmax)
		x = old_x - x > 0 ? -x : 0;
	if (old_y + y >= ymax)
		y = old_y - y > 0 ? -y : 0;
	std::cout << '(' << x << ',' << y << ")\n";
	image.move(x, y);
	button.move(x, y);
}
