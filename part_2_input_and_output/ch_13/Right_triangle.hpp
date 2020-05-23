#ifndef RIGHT_TRIANGLE_HPP
#define RIGHT_TRIANGLE_HPP
#include <graphics/Graph.h>

using namespace Graph_lib;

class Right_triangle : public Polygon
{
public:
	Right_triangle(Point a, Point b, Point c);
};

bool is_right_triangle(Point a, Point b, Point c);
double distance(Point a, Point b);
#endif // !RIGHT_TRIANGLE_HPP
