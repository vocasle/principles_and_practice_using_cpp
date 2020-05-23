#include "Star.hpp"

Star::Star(Point c, int circumradius, int p, int q): Open_polyline(), p(p), q(q)
{
	if (p < 5 || q > p / 2)
		error("Invalid values for p and q. Either p is less than 5 or q is greater than p/2.");
	if (circumradius <= 0)
		error("Circumradius could not be negative or equal to zero.");
	if (!are_relatively_prime(p, q))
		error("p and q must be relatively prime.");

	for (auto& p : points_on_circle(c, circumradius, p))
		Open_polyline::add(p);	
}

void Star::draw_lines() const
{
	for (auto i = 0; i < number_of_points(); ++i)
	{
		auto next = i + q >= p ? i + q - p : i + q;
		fl_line(point(i).x, point(i).y, point(next).x, point(next).y);
	}
}

int gcd(int m, int n)
{
	auto gcd = 1;
	for (auto i = 2; i <= min(m, n); ++i)
	{
		if (m % i == 0 && n % i == 0)
			gcd = i;
	}
	return gcd;
}

bool are_relatively_prime(int m, int n)
{
	return gcd(m,n) == 1;
}

vector<Point> points_on_circle(Point c, int radius, int n)
{
	if (radius <= 0 || n <= 0)
		error("Either radius or n is less than or equal to zero.");

	static constexpr auto pi = 3.1416;
	auto points = vector<Point>();
	auto angle = 2* pi / n;
	auto t = angle;
	while (points.size() != n)
	{
		auto x = c.x + radius * cos(t);
		auto y = c.y + radius * sin(t);
		points.emplace_back(x, y);
		t += angle;
	}
	return points;
}
