#include <graphics/Simple_window.h>

template <typename T>
class Group
{
public:
	Group() : list{} 
	{
		if (!is_base_of<Shape, T>::value)
			error("T must be an instance of Shape!");
	}
	void push_back(T el) { list.push_back(el); }
	size_t size() { return list.size(); }
	T& operator[](size_t i) { return *(list.begin() + i); }
private:
	vector<T> list;
};

struct A {};

int main()
{
	auto win = Simple_window{ {100, 100}, 800, 600, "Exercise 9" };
	auto grp = Group<Rectangle>();
	for (auto i = 0; i < 64; ++i)
		grp.push_back(Rectangle({ 0, 0 }, 75, 75));

	for (auto i = 0; i < grp.size(); ++i)
	{
		win.attach(grp[i]);
		auto x = 75 * (i % 8);
		auto y = 75 * (i / 8);
		grp[i].move(x, y);
		auto color =  i % 2 == 0 ? Color::white : Color::black;
		if ((i / 8) % 2 == 0)
			color = i % 2 != 0 ? Color::white : Color::black;
		grp[i].set_fill_color(color);
	}
	win.wait_for_button();
}