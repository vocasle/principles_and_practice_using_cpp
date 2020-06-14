#include <graphics/Window.h>
#include "Bar.hpp"

int main()
{
	using namespace Graph_lib;
	vector<double> spb_usa_temps{ 21.1,21.7,24.4,27.2,30,31.7,32.2,32.2,31.7,28.9,25,22.2 };
	vector<double> spt_rus_temps{ -3,-3,2,9,16,20,23,21,15,9,2,-2 };

	constexpr int min_temp = -5;
	constexpr int max_temp = 35;
	constexpr int width = 800;
	constexpr int height = 600;
	constexpr int margin = 40;

	const string xlabel = "jan          feb          mar          apr          may          jun          jul          aug          sep          oct          nov          dec";
	const string ylabel = "Temperatures: [-5,35]";

	Window win = Window({ 100, 100 }, width, height, "Exercise 11");
	Axis ox = Axis(Axis::x, { margin, height - margin - 5 * ((height - margin * 2) / 40) }, width - margin * 2, 12, xlabel);
	ox.label.move(-185, 0);
	Axis oy = Axis(Axis::y, { margin, height - margin }, height - margin * 2, 40, ylabel);

	ox.set_color(Color::red);
	oy.set_color(Color::red);

	double xscale = double(width - margin * 2) / 12;
	double yscale = double(height - margin * 2) / (max_temp - min_temp);
	
	Bar bar_usa = Bar(ox.point(0), spb_usa_temps, int(round(xscale)), int(round(yscale)));
	for (size_t n = 0; n < bar_usa.num_of_bars(); ++n)
		bar_usa.set_fill_color(n, Color::green);

	Bar bar_rus = Bar(ox.point(0), spt_rus_temps, int(round(xscale)), int(round(yscale)));
	for (size_t n = 0; n < bar_rus.num_of_bars(); ++n)
		bar_rus.set_fill_color(n, Color::yellow);
	win.attach(bar_usa);
	win.attach(bar_rus);
	win.attach(ox);
	win.attach(oy);
	gui_main();
}