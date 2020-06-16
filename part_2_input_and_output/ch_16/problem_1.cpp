#include <graphics/Window.h>
#include <graphics/GUI.h>

using namespace Graph_lib;

class My_window : public Window
{
public:
	My_window(Point xy, int w, int h, const string& lbl)
		: Window(xy, w, h, lbl),
		next_btn{ Point{x_max() - 150, 0}, 70, 20, "Next",
			[](Address, Address pw) {reference_to<My_window>(pw).next(); }
	},
		quit_btn{ Point{x_max() - 70, 0}, 70, 20, "Quit",
			[](Address, Address pw) {reference_to<My_window>(pw).quit(); }
	}
	{
		attach(quit_btn);
		attach(next_btn);
	}
private:
	Button quit_btn;
	Button next_btn;
	void quit() { hide(); }
	void next() {}
};

int main()
try
{
	My_window win{ Point{100,100}, 600,400,"Exercise 1" };
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