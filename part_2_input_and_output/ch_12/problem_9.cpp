// Displays an image with caption

#include <graphics/Simple_window.h>

int main()
{
	auto win = Simple_window{ Point{100, 100}, 800, 600, "Exercise 9 - Autumn leaves" };
	auto img = Image{ Point{0,0}, "leaves.jpg" };
	auto caption = Text{ Point{50, 500}, "Autumn leaves" };
	caption.set_font_size(30);
	caption.set_color(Color::white);
	win.attach(img);
	win.attach(caption);
	win.wait_for_button();
}