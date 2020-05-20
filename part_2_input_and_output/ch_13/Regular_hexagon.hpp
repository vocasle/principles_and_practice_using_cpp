#ifndef REGULAR_HEXAGON_HPP
#define REGULAR_HEXAGON_HPP
#include "Regular_polygon.hpp"

class Regular_hexagon : public Regular_polygon
{
public:
	Regular_hexagon(Point center, unsigned int circumradius);
};
#endif // !REGULAR_HEXAGON_HPP
