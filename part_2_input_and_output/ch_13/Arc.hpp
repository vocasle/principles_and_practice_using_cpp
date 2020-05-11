#ifndef ARC_HPP
#define ARC_HPP

#include <graphics/Graph.h>

// Represents an arc.
// Arc can be defined by radius and central angle.
// Consult https://en.wikipedia.org/wiki/Arc_(geometry)
class Arc : public Graph_lib::Circle
{
public:
	// center - a center of the arc
	// radius - radius of the arc
	// angle - angle of the central angle in degrees
	Arc(Graph_lib::Point center, int radius, double angle);
	void draw_lines() const;
	// Returns the get_length of the arc
	double get_length() const;
private:
	static constexpr auto pi = 3.14159265;
	double m_angle;
	int m_radius;
};



#endif // !ARC_HPP
