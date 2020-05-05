#include <graphics/Simple_window.h>

int main()
{
	using namespace Graph_lib;
	auto tl = Point{ 100, 100 };
	// Make a window
	auto win = Simple_window{ 
		tl, // place top left corner of window in (100,100)
		600, // width in px
		400, // height in px
		"Canvas" }; // title
	// Add X axis
	auto xa = Axis{ 
		Axis::x, // axis type
		Point{20, 300}, // starting point
		280, // width in px
		10, // amount of notches
		"x axis" }; // label
	win.attach(xa);
	// Add Y axis
	auto ya = Axis{ Axis::y, Point{20, 300}, 280, 10, "y axis" };
	win.attach(ya);
	// Draw a sine function
	Function sine{ 
		sin, // math function
		0, 100, // range [0, 100)
		Point{20, 150}, // starting point
		1000, // amount of points used to draw
		50, // scale x values 
		50 }; // scale y values
	sine.set_color(Color::blue);
	win.attach(sine);
	// Draw a triangle
	// Polygon connects each point to the next one. The last one will be connected with first
	auto poly = Polygon{};
	poly.add(Point{ 300, 200 });
	poly.add(Point{ 350, 100 });
	poly.add(Point{ 400, 200 });
	poly.set_color(Color::red);
	poly.set_style(Line_style::dashdot);
	win.attach(poly);
	// Draw a rectangle
	auto r = Rectangle{ 
		Point{200, 200}, // starting point
		100, // width in px
		50 }; // height in px
	win.attach(r);
	// Draw a polyline
	auto poly_rect = Closed_polyline{};
	poly_rect.add(Point{ 100, 50 });
	poly_rect.add(Point{ 200, 50 });
	poly_rect.add(Point{ 200, 100 });
	poly_rect.add(Point{ 100, 100 });
	poly_rect.add(Point{ 50, 75 });
	win.attach(poly_rect);
	// Fill shapes with colour
	r.set_fill_color(Color::yellow);
	poly.set_style(Line_style(Line_style::dash, 4));
	poly_rect.set_style(Line_style(Line_style::dash, 2));
	poly_rect.set_fill_color(Color::green);
	// Draw text
	auto t = Text{ Point{150, 150}, // starting point
		"Hello, graphical world!" }; // text to display
	win.attach(t);
	// Change text style
	t.set_font(Font::times_bold);
	t.set_font_size(20);
	// Add image
	auto ii = Image{ Point{100, 50}, // starting point
		"cat.jpg" }; // path to image
	win.attach(ii);
	ii.move(300, 200);
	// Add circle
	auto c = Circle{ Point{100, 200}, // starting point (center of the circle)
		50 }; // radius
	// Add ellipse
	auto e = Ellipse{ Point{100, 200}, // middle of the ellipse
		75, // bigger radius in px
		25 }; // smaller radius in px
	e.set_color(Color::dark_red);
	// Add mark
	auto m = Mark{ Point{100, 200}, // starting point
		'x' }; // mark
	// Add text with sizes
	auto oss = ostringstream{};
	oss << "screen size: " << x_max() << "*" << y_max()
		<< "; window size: " << win.x_max() << "*" << win.y_max();
	auto sizes = Text{ Point{100, 20}, oss.str() };
	// Add gif image
	auto gif = Image{ Point{255, 255}, "cat.gif" };
	gif.set_mask(Point{ 40, 40 }, 200, 150);
	win.attach(c);
	win.attach(e);
	win.attach(m);
	win.attach(sizes);
	win.attach(gif);
	win.wait_for_button();
};