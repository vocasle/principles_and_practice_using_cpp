#ifndef BOX_HPP
#define BOX_HPP

#include <graphics/Graph.h>
#include <graphics/Point.h>

// Box class creates a rectangle with rounded corners.
// Changing side length and corner radius after construction is prohibited.
// It is a design choise due to the fact that maximum corner radius is a half of the side length.
// And I could not come with a good default for cases when radius is bigger that half of the side length.
class Box : public Graph_lib::Closed_polyline
{
public:
	Box(Graph_lib::Point top_left, int side_length, int corner_radius, unsigned int span = 10);
	int get_side_length() const { return m_side_length; }
	int get_corner_radius() const { return m_corner_radius; }
private:
	const unsigned int m_span;
	const int m_side_length;
	const int m_corner_radius;
	const Graph_lib::Point m_top_left;
};

vector<Graph_lib::Point> get_arc_points(Graph_lib::Point center, int radius, double start, double end, unsigned int span);
vector<Graph_lib::Point> generate_guide_line_points(Graph_lib::Point top_left, int side_length, int corner_radius, unsigned int span);
#endif // !BOX_HPP
