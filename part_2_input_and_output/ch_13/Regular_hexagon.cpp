#include "Regular_hexagon.hpp"

Regular_hexagon::Regular_hexagon(Point center, unsigned int circumradius) : Regular_polygon(center, circumradius, 6)
{
	if (circumradius == 0)
	{
		error("Distance could not be equal to zero.");
	}
}