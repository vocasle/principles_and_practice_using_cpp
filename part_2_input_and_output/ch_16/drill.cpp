#include <graphics/GUI.h>
#include <graphics/Window.h>

using namespace Graph_lib;

class Lines_window : public Window
{
public:
	Lines_window(Point xy, int w, int h, const string& title);
private:
	Open_polyline lines;
	Menu color_menu;
	Menu style_menu;
	Button next_button;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;

	void next();
	void quit();

	void red_pressed() { change_color(Color::red); }
	void blue_pressed() { change_color(Color::blue); }
	void black_pressed() { change_color(Color::black); }
	void change_color(Color c) { lines.set_color(c); redraw(); }

	void dash_pressed() { change_style(Line_style::dash); }
	void dash_dot_pressed() { change_style(Line_style::dashdot); }
	void dash_dot_dot_pressed() { change_style(Line_style::dashdotdot); }
	void change_style(Line_style s) { lines.set_style(s); redraw(); }
};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window{ xy, w, h, title },
	color_menu{Point{x_max() - 70, 40}, 70, 20, Menu::vertical, "color"},
	style_menu{ Point{x_max() - 150, 40}, 70, 20, Menu::vertical, "style" },
	next_button{ Point{x_max() - 150, 0}, 70, 20, "Next point",
[](Address, Address pw) {reference_to<Lines_window>(pw).next(); }
},
quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit",
[](Address, Address pw) {reference_to<Lines_window>(pw).quit(); }
},
next_x{ Point{x_max() - 310, 0}, 50, 20, "next x:" },
next_y{ Point{x_max() - 210, 0}, 50, 20, "next y:" },
xy_out{ Point{100,0}, 100, 20, "current (x,y):" }
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	attach(lines);
	color_menu.attach(new Button(Point{ 0,0 }, 0, 0, "red", [](Address, Address pw) {reference_to<Lines_window>(pw).red_pressed(); }));
	color_menu.attach(new Button(Point{ 0,0 }, 0, 0, "blue", [](Address, Address pw) {reference_to<Lines_window>(pw).blue_pressed(); }));
	color_menu.attach(new Button(Point{ 0,0 }, 0, 0, "black", [](Address, Address pw) {reference_to<Lines_window>(pw).black_pressed(); }));
	style_menu.attach(new Button(Point{ 0,0 }, 0, 0, "dash", [](Address, Address pw) {reference_to<Lines_window>(pw).dash_pressed(); }));
	style_menu.attach(new Button(Point{ 0,0 }, 0, 0, "dash dot", [](Address, Address pw) {reference_to<Lines_window>(pw).dash_dot_pressed(); }));
	style_menu.attach(new Button(Point{ 0,0 }, 0, 0, "dash dots", [](Address, Address pw) {reference_to<Lines_window>(pw).dash_dot_dot_pressed(); }));
	attach(color_menu);
	attach(style_menu);
}

void Lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();
	lines.add(Point{ x,y });
	// update current position redout:
	ostringstream oss;
	oss << '(' << x << ',' << y << ')';
	xy_out.put(oss.str());

	redraw();
}

void Lines_window::quit()
{
	hide();
}

int main()
try
{
	Lines_window win{ Point{100,100}, 600,400,"lines" };
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