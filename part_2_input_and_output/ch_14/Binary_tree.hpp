#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP
#include <graphics/Graph.h>
#include <list>
using namespace Graph_lib;

typedef int NodeElement;

struct Node
{
	Point p;
	Text t;
	Node* left;
	Node* right;
	Node* parent;
	Node() : left{ nullptr }, right{ nullptr }, parent{ nullptr }, p{}, t{ {0,0}, "" } {}
};

class Binary_tree : public Shape
{
public:
	virtual ~Binary_tree();
	Binary_tree(unsigned int levels, Point c, unsigned int scale = 10);
	Node* get_root() const;
	void draw_lines() const;
	virtual void draw_node(Node* n) const;
	void gen_points(Node* n, vector<Point>& points);
private:
	Node* root = nullptr;
	Point center;
	unsigned int scale;
};

void populateTree(Node* root, unsigned int lvl);
size_t depth(Node* n);
bool isExternal(Node* n);
void preorderDelete(Node* n);
#endif // !BINARY_TREE_HPP
