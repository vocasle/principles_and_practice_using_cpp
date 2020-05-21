#include <graphics/Simple_window.h>

int main()
{
	auto win = Simple_window({ 100, 100 }, 800, 600, "Exercise 13");
	Vector_ref<Rectangle> vr;
	for (int i = 0; i < 16; ++i)
		for (int j = 0; j < 16; ++j)
		{
			vr.push_back(new Rectangle{ Point{i * 20,j * 20},20,20 });
			vr[vr.size() - 1].set_fill_color(Color{ i * 16 + j });
			vr[vr.size() - 1].set_color(Color::invisible);
			win.attach(vr[vr.size() - 1]);
		}
	win.wait_for_button();
}