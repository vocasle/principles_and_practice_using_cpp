#include <graphics/Simple_window.h>
#include "Binary_tree.hpp"

class Binary_tree_rect : public Binary_tree
{
public:
	Binary_tree_rect(unsigned int lvls, Point c) : Binary_tree(lvls, c), center{ c } {}
	void draw_node(Node* n) const
	{
		if (!isExternal(n))
		{
			if (color().visibility())
			{
				fl_color(color().as_int());
				fl_line(n->p.x + center.x, n->p.y + center.y, n->left->p.x + center.x, n->left->p.y + center.y);
				fl_line(n->p.x + center.x, n->p.y + center.y, n->right->p.x + center.x, n->right->p.y + center.y);
				fl_color(color().as_int());	// reset color
			}
			draw_node(n->left);
			draw_node(n->right);
		}
		if (fill_color().visibility())
		{
			fl_color(fill_color().as_int());
			fl_rectf(n->p.x + center.x - 5, n->p.y + center.y - 5, 10, 10);
			fl_color(color().as_int());	// reset color
		}
	}
private:
	Point center;
};

int main()
{
	try
	{
		auto win = Simple_window{ {100, 100}, 800, 600, "Exercise 11" };
		auto bt = Binary_tree_rect(6, { 100, 300 });
		bt.set_fill_color(Color::yellow);
		bt.set_color(Color::blue);
		win.attach(bt);
		win.wait_for_button();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unexpected exception\n";
		return 2;
	}
}