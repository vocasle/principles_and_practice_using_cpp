#include <graphics/Simple_window.h>

int main()
{
	auto win = Simple_window{ {100, 100}, 800, 600, "Exercise 7" };
	auto rects = vector<Rectangle>();
	static constexpr const auto side_length = 20;
	for (auto i = 0; i < 16; ++i)
	{
		for (auto j = 0; j < 16; ++j)
		{
			rects.emplace_back(Point{ side_length * j, side_length * i }, side_length, side_length);
			rects.at(rects.size() - 1).set_fill_color(rects.size() - 1);
		}
	}

	for (auto& r : rects)
	{
		win.attach(r);
	}
	win.wait_for_button();
}