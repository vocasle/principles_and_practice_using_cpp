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
	},
		out(Point(x_max() - 230, 0), 70, 20, "coords:")
	{
		attach(quit_btn);
		attach(next_btn);
		attach(out);
		for (size_t n = 0; n < 16; ++n)
		{
			buttons.push_back(new Button(
				Point(70 + 70 * (n % 4), 20 + 20 * (n / 4)),
				70,
				20,
				"Button " + to_string(n),
				[](Address b, Address pw) { 
					ostringstream oss;
					oss << '(' << reference_to<Fl_Button>(b).x()
						<< ',' << reference_to<Fl_Button>(b).y() << ')';
					reference_to<My_window>(pw).out.put(oss.str());
				}));
		}
		for (size_t n = 0; n < buttons.size(); ++n)
			attach(buttons[n]);
	}
private:
	Button quit_btn;
	Button next_btn;
	Out_box out;
	void quit() { hide(); }
	void next() {}
	Vector_ref<Button> buttons;
	void print(const string& lbl) { cout << lbl << '\n'; }
};

int main()
try
{
	My_window win{ Point{100,100}, 600,400,"Exercise 2" };
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