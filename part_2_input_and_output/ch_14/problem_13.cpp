#include <graphics/Simple_window.h>
#include "Binary_tree.hpp"

enum class ArrowDirection
{
	forward, backward
};

class Binary_tree_arr : public Binary_tree
{
public:
	Binary_tree_arr(unsigned int lvls, Point c, ArrowDirection ad) : Binary_tree(lvls, c, 50), ad{ ad }, center{ c }
	{
	}
	void draw_node(Node* n) const
	{
		if (!isExternal(n))
		{
			if (color().visibility())
			{
				fl_color(color().as_int());
				auto [a, b] = calcVertexes({ n->p.x + center.x, n->p.y + center.y },
					{ n->right->p.x + center.x, n->right->p.y + center.y });
				auto [c, d] = calcVertexes({ n->p.x + center.x, n->p.y + center.y },
					{ n->left->p.x + center.x, n->left->p.y + center.y });
				if (ad == ArrowDirection::forward)
				{
					fl_polygon(a.x, a.y, b.x, b.y, n->right->p.x + center.x, n->right->p.y + center.y);
					fl_polygon(c.x, c.y, d.x, d.y, n->left->p.x + center.x, n->left->p.y + center.y);
				}
				else
				{
					fl_polygon(a.x, a.y, b.x, b.y, n->p.x + center.x, n->p.y + center.y);
					fl_polygon(c.x, c.y, d.x, d.y, n->p.x + center.x, n->p.y + center.y);
				}
				fl_line(a.x + center.x, a.y + center.y, b.x + center.x, b.y + center.y);
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
			fl_pie(n->p.x + center.x - 5, n->p.y + center.y - 5, 10, 10, 0, 360);
			fl_color(color().as_int());	// reset color
		}
	}
private:
	Point center;
	ArrowDirection ad;
	// calculates left and right points for arrows
	pair<Point, Point> calcVertexes(Point a, Point b) const
	{
		static constexpr unsigned int arrow_length = 15;
		static constexpr unsigned int arrow_width = 5;
		// vector from point a to point b
		const Point vec_ab = Point{ b.x - a.x, b.y - a.y };
		// length of the vector from point a to b
		const double d_ab = sqrt(pow(vec_ab.x, 2) + pow(vec_ab.y, 2));
		// point c is a point arrow_length px aside from end of the vector from point a to b along this vector
		Point c;
		if (ad == ArrowDirection::forward)
		{
			c = Point{ 
				static_cast<int>(b.x - (double(b.x) - double(a.x)) * arrow_length / d_ab),
				static_cast<int>(b.y - (double(b.y) - double(a.y)) * arrow_length / d_ab)
			};
		}
		else
		{
			c = Point{
				static_cast<int>(a.x + (double(b.x) - double(a.x)) * arrow_length / d_ab),
				static_cast<int>(a.y + (double(b.y) - double(a.y)) * arrow_length / d_ab)
			};
		}

		const Point p1 = Point{
			static_cast<int>(c.x + arrow_width * (-vec_ab.y / d_ab)),
			static_cast<int>(c.y + arrow_width * (vec_ab.x / d_ab))
		};

		const Point p2 = Point{
			static_cast<int>(c.x + arrow_width * (vec_ab.y / d_ab)),
			static_cast<int>(c.y + arrow_width * (-vec_ab.x / d_ab))
		};
		
		return { p1,p2 };
	}
};

int main()
{
	try
	{
		auto win = Simple_window{ {100, 100}, 800, 600, "Exercise 11" };
		auto bt = Binary_tree_arr(4, { 50, 300 }, ArrowDirection::forward);
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