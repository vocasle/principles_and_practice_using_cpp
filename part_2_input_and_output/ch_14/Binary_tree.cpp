#include "Binary_tree.hpp"

Binary_tree::~Binary_tree()
{
	preorderDelete(root);
}

Binary_tree::Binary_tree(unsigned int levels, Point c, unsigned int scale) : Shape(), center{c}, scale{scale}
{
	switch (levels)
	{
	case 0:
		break;
	case 1:
		root = new Node();
		break;
	default:
		root = new Node();
		populateTree(root, levels - 1);
	}
	vector<Point> points;
	gen_points(get_root(), points);
}

Node* Binary_tree::get_root() const
{
	if (!root)
		error("Binary_tree has no root!");
	return root;
}

void Binary_tree::draw_lines() const
{
	draw_node(root);
}

void Binary_tree::draw_node(Node* n) const
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
		n->t.draw_lines();
		fl_pie(n->p.x + center.x - 5, n->p.y + center.y - 5, 10, 10, 0, 360);
		fl_color(color().as_int());	// reset color
	}
}

void populateTree(Node* root, unsigned int lvl)
{
	Node* l = new Node();
	Node* r = new Node();
	l->parent = root;
	r->parent = root;
	root->left = l;
	root->right = r;
	if (lvl == 1)
		return;
	populateTree(l, lvl - 1);
	populateTree(r, lvl - 1);
}

void getNodes(Node* root, std::list<Node*>& list)
{
	list.push_back(root);
	if (root->left)
		getNodes(root->left, list);
	if (root->right)
		getNodes(root->right, list);
}

size_t depth(Node* n)
{
	if (n->parent)
		return 1 + depth(n->parent);
	return 0;
}

void  Binary_tree::gen_points(Node* n, vector<Point>& points)
{
	if (!isExternal(n))
		gen_points(n->left, points);
	Point p = Point(points.size() * scale, depth(n) * scale);
	Text t = Text{ {p.x + center.x, p.y + center.y}, to_string(depth(n)) };
	n->p = p;
	n->t = t;
	points.emplace_back(p);
	if (!isExternal(n))
		gen_points(n->right, points);
}

bool isExternal(Node* n)
{
	return !(n->left && n->right);
}

void preorderDelete(Node* n)
{
	if (isExternal(n))
		delete n;
	else
	{
		preorderDelete(n->left);
		preorderDelete(n->right);
	}
}
