#include <graphics/Simple_window.h>

int main()
{
	constexpr auto square_size = 100;
	auto win = Simple_window{ Point{square_size, square_size}, 800, 1000, "Drill" };
	auto grid = vector<Rectangle>();
	for (auto i = 0; i < 8; ++i)
	{
		for (auto j = 0; j < 8; ++j)
		{
			grid.push_back(Rectangle{ Point{i * square_size, j * square_size}, square_size, square_size });
		}
	}

	for (auto i = 0; i < grid.size(); ++i)
	{
		if (i == 0 || i % 9 == 0)
		{
			grid[i].set_fill_color(Color::red);
		}
		win.attach(grid[i]);
	}

	auto img1 = Image{ Point{win.x_max() - square_size * 4, 0}, "img.jpg" };
	auto img2 = Image{ Point{win.x_max() - square_size * 2, 200}, "img.jpg" };
	auto img3 = Image{ Point{win.x_max() - square_size * 4, 200}, "img.jpg" };
	auto img = Image{ Point{0, 0}, "small.gif" };
	win.attach(img1);
	win.attach(img2);
	win.attach(img3);
	win.attach(img);
	win.wait_for_button();

	auto row = 0;
	auto cell = 1;
	constexpr auto x_max = square_size * 8;
	while (true)
	{
		auto p = img.point(0);
		auto x = p.x + square_size == x_max ? square_size - x_max : square_size;
		cell = cell == grid.size() ? 0 : cell;
		row = cell / 8;
		auto y = 0;
		if (p.y + square_size == x_max && row == 0)
		{
			y = square_size - x_max;
		}
		else
		{
			y = p.y / square_size == row ? 0 : square_size;
		}
		
		img.move(x, y);
		win.wait_for_button();
		++cell;
	}
}