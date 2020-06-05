#include<graphics/Simple_window.h>
#include "Binary_tree.hpp"



int main()
{
	Simple_window win = Simple_window{ {100, 100}, 800, 600, "Exercise 14" };
	Binary_tree bt = Binary_tree{ 5, { 100, 300 }, 20 };
	bt.set_fill_color(Color::white);
	bt.get_root()->t.set_label("root");
	bt.get_root()->t.draw_lines();
	win.attach(bt);
	win.wait_for_button();
}