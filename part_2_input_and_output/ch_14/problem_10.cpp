#include <graphics/Simple_window.h>
#include "Pseudo_window.hpp"

int main()
{
	auto win = Simple_window({ 100, 100 }, 800, 600, "Exercise 10");
	auto pw = Pseudo_window({ 100, 100 }, 400, 300, "Test window");
	auto img = Image({ 100, 100 }, "index.jpg");
	win.attach(pw);
	pw.set_title("Window");
	pw.attach(&img);
	win.wait_for_button();
}