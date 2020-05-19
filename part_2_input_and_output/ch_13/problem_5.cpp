#include <graphics/Simple_window.h>
#include "connection_points.hpp"

int main()
{
	auto win = Simple_window{ {100, 100}, 800, 600, "Exercise 5" };
	auto labels = vector<Text>();
	auto circle = Circle{ {200, 200}, 100 };
	labels.emplace_back(n(circle), point_to_string(n(circle)));
	labels.emplace_back(s(circle), point_to_string(s(circle)));
	labels.emplace_back(e(circle), point_to_string(e(circle)));
	labels.emplace_back(w(circle), point_to_string(w(circle)));
	labels.emplace_back(center(circle), point_to_string(center(circle)));
	labels.emplace_back(ne(circle), point_to_string(ne(circle)));
	labels.emplace_back(se(circle), point_to_string(se(circle)));
	labels.emplace_back(sw(circle), point_to_string(sw(circle)));
	labels.emplace_back(nw(circle), point_to_string(nw(circle)));

	auto ellipse = Ellipse{ {600, 300}, 100, 200 };
	labels.emplace_back(n(ellipse), point_to_string(n(ellipse)));
	labels.emplace_back(s(ellipse), point_to_string(s(ellipse)));
	labels.emplace_back(e(ellipse), point_to_string(e(ellipse)));
	labels.emplace_back(w(ellipse), point_to_string(w(ellipse)));
	labels.emplace_back(center(ellipse), point_to_string(center(ellipse)));
	labels.emplace_back(ne(ellipse), point_to_string(ne(ellipse)));
	labels.emplace_back(se(ellipse), point_to_string(se(ellipse)));
	labels.emplace_back(sw(ellipse), point_to_string(sw(ellipse)));
	labels.emplace_back(nw(ellipse), point_to_string(nw(ellipse)));

	win.attach(circle);
	win.attach(ellipse);
	for (auto& lbl : labels)
	{
		win.attach(lbl);
	}
	win.wait_for_button();
}