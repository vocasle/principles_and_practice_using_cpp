// Draws 3x3 tic-tac-toe board

#include <graphics/Simple_window.h>

int main()
{
	using namespace Graph_lib;
	constexpr auto win_width = 800;
	constexpr auto win_height = 600;
	const auto p = Point{ 100, 100 };
	auto win = Simple_window{ p, win_width, win_height, "Exercise 4" };
	constexpr auto rect_side = 100;
	auto col_cnt = 1;
	constexpr auto size = 9;
	auto rects = vector<Rectangle>();

	for (auto i = 0; i < size; ++i)
	{
		auto row_cnt = i < 3 ? 1 : i < 6 ? 2 : 3;
		auto tl = Point{ 100 * col_cnt, 100 * row_cnt };
		auto rect = Rectangle{ tl, rect_side, rect_side };
		if (i % 2 == 0)
		{
			rect.set_fill_color(Color::white);
		}
		else
		{
			rect.set_fill_color(Color::red);
		}
		rects.push_back(rect);
		
		++col_cnt;
		if (col_cnt > 3)
		{
			col_cnt = 1;
		}
	}

	for (auto& rect : rects)
	{
		win.attach(rect);
	}

	win.wait_for_button();
}