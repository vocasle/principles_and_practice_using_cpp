#include "Bar.hpp"
#include <graphics/Window.h>

struct Distribution
{
	int height;
	int num_in_grp;
};

istream& operator>>(istream& is, Distribution& d)
{
	char ch1 = 0;
	char ch2 = 0;
	char ch3 = 0;
	Distribution dist;
	if (is >> ch1 >> dist.height >> ch2 >> dist.num_in_grp >> ch3)
	{
		if (ch1 != '(' || ch2 != ',' || ch3 != ')')
			is.clear(ios::failbit);
		else
			d = dist;
	}
	return is;
}

ostream& operator<<(ostream& os, const Distribution& d)
{
	os << '(' << d.height << ',' << d.num_in_grp << ')';
	return os;
}

vector<Distribution> read_distribution(const string& file_name, int min_height, int max_height)
{
	ifstream ifs{ file_name };
	if (!ifs)
		error("cannot open", file_name);
	vector<Distribution> dists;
	for (Distribution d; ifs >> d;)
	{
		if (d.height > max_height || d.height < min_height)
			error("invalid height for human: ", d.height);
		if (d.num_in_grp <= 0)
			error("invalid number of people in group: ", d.num_in_grp);
		dists.push_back(d);
	}
	return dists;
}

int main()
{
	using namespace Graph_lib;
	constexpr int width = 800;
	constexpr int height = 600;
	constexpr int xoff = 40;
	constexpr int yoff = 20;
	constexpr int xlen = width - xoff * 2;
	constexpr int ylen = height - yoff * 2;
	static constexpr int min_height = 71;
	static constexpr int max_height = 300;

	const Point orig = Point(width / 2, height / 2);
	Window win = Window(orig, width, height, "Exercise 8");

	auto dists = read_distribution("distribution.txt", min_height, max_height);

	Axis ox{ Axis::x, Point{xoff, height - yoff}, xlen };
	Axis oy{ Axis::y, Point{xoff, height - yoff}, ylen };
	win.attach(ox);
	win.attach(oy);
	vector<double> nums;
	for_each(dists.begin(), dists.end(), [&](const Distribution& d) {
		nums.push_back(d.num_in_grp);
		});

	auto [min_age, max_age] = minmax_element(nums.begin(), nums.end());
	double yscale = double(ylen) / (*max_age - *min_age);
	
	Bar bar = Bar({xoff, height - yoff}, nums, 25, int(yscale));
	win.attach(bar);

	for (size_t i = 0; i < bar.num_of_bars(); ++i)
	{
		bar.set_fill_color(i, Color::dark_magenta);
		bar.set_label(i, to_string(dists.at(i).height), Color::white);
	}

	gui_main();
}