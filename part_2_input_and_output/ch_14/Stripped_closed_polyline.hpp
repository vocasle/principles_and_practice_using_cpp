#ifndef STRIPPED_CLOSED_POLYLINE_HPP
#define STRIPPED_CLOSED_POLYLINE_HPP
#include <graphics/Graph.h>
using namespace Graph_lib;
class Stripped_closed_polyline : public Closed_polyline
{
public:
	using Closed_polyline::Closed_polyline;
	void draw_lines() const;
	void add(Point p);
private:
	int y_min = INT_MAX;
	int x_min = INT_MAX;
	int y_max = -1;
	int x_max = -1;
	void recalc_bounding_rect();
	vector<Line> get_edges() const;
};

// determines wether polygon width edges edges contains a point p
bool includes(const Point& p, const vector<Line>& edges);
#endif // !STRIPPED_CLOSED_POLYLINE_HPP
