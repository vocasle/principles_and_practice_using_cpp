#ifndef STAR_HPP
#define STAR_HPP
#include "Regular_polygon.hpp"
class Star : public Open_polyline
{
public:
	Star(Point c, int circumradius, int p, int q);
	void draw_lines() const;
private:
	static constexpr auto pi = 3.1416;
	const int p;
	const int q;
};

int gcd(int m, int n);
bool are_relatively_prime(int m, int n);
vector<Point> points_on_circle(Point c, int radius, int n);
#endif // !STAR_HPP
