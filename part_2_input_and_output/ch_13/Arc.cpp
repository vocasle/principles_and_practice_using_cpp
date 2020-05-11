#include "Arc.hpp"

Arc::Arc(Graph_lib::Point center, int radius, double degrees): Graph_lib::Circle{center, radius}, m_angle{degrees}, m_radius{radius}
{

}

void Arc::draw_lines() const
{
	if (color().visibility())
	{
		fl_arc(point(0).x, point(0).y, m_radius + m_radius, m_radius + m_radius, 0, m_angle);
	}
}

double Arc::get_length() const
{
	return m_angle * m_radius * (pi / 180);
}
