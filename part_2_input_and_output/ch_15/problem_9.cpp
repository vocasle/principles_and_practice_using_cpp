#include <graphics/Window.h>
#include "Bar.hpp"

struct Distribution
{
	int idx;
	double height;
	double weight;
};

istream& operator>>(istream& is, Distribution& d)
{
	Distribution dist;
	if (is >> dist.idx >> dist.height >> dist.weight)
		d = dist;
	return is;
}

ostream& operator<<(ostream& os, const Distribution& d)
{
	os << '(' << d.idx << ' ' << d.height << ' '<<  d.weight << ')';
	return os;
}

vector<Distribution> read_distribution(const string& file_name, int min_height, int max_height)
{
	ifstream ifs{ file_name };
	if (!ifs)
		error("cannot open", file_name);
	vector<Distribution> dists;
	for (Distribution d; ifs >> d;)
		dists.push_back(d);
	return dists;
}

void remove_duplicates(vector<double>& v)
{
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it)
		end = remove(it + 1, end, *it);

	v.erase(end, v.end());
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

	auto dists = read_distribution("distribution_usa.txt", min_height, max_height);
	vector<double> heights;
	for_each(dists.begin(), dists.end(), [&](const Distribution d) {
		heights.push_back(round(d.height));
		});
	remove_duplicates(heights);
	Axis ox{ Axis::x, Point{xoff, height - yoff}, xlen };
	Axis oy{ Axis::y, Point{xoff, height - yoff}, ylen };
	win.attach(ox);
	win.attach(oy);

	auto [min_age, max_age] = minmax_element(heights.begin(), heights.end());

	Bar bar = Bar({ xoff, height - yoff }, heights, 25, 2);
	win.attach(bar);

	for (size_t i = 0; i < bar.num_of_bars(); ++i)
	{
		bar.set_fill_color(i, Color::dark_magenta);
		bar.set_label(i, to_string(dists.at(i).height), Color::white);
	}

	gui_main();
}