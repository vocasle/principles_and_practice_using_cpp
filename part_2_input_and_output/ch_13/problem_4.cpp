#include <graphics/Simple_window.h>
#include "connection_points.hpp"

int main()
{
	auto win = Simple_window{ Point{100, 100}, 800, 600, "Exercise 4" };
	auto rect = Rectangle{ {200,200}, 400, 200 };
	auto labels = vector<Text>();
	labels.emplace_back(n(rect), point_to_string(n(rect)));
	labels.emplace_back(s(rect), point_to_string(s(rect)));
	labels.emplace_back(e(rect), point_to_string(e(rect)));
	labels.emplace_back(w(rect), point_to_string(w(rect)));
	labels.emplace_back(center(rect), point_to_string(center(rect)));
	labels.emplace_back(ne(rect), point_to_string(ne(rect)));
	labels.emplace_back(se(rect), point_to_string(se(rect)));
	labels.emplace_back(sw(rect), point_to_string(sw(rect)));
	labels.emplace_back(nw(rect), point_to_string(nw(rect)));
	for (auto& lbl : labels)
	{
		win.attach(lbl);
	}
	win.attach(rect);
	win.wait_for_button();
}