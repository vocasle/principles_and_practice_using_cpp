#ifndef POLY_HPP
#define POLY_HPP
#include <graphics/Graph.h>
using namespace Graph_lib;
// A simple wrapper around Polygon class, that allows to initialize 
// with initializer_list<Point>.
class Poly : public Polygon
{
public:
	Poly(initializer_list<Point> points);
};
#endif // !POLY_HPP
