#ifndef CIRCLE_CONNECTION_POINTS_HPP
#define CIRCLE_CONNECTION_POINTS_HPP
#include <graphics/Graph.h>
using namespace Graph_lib;
Point n(const Rectangle& r)
{
	return { r.point(0).x + r.width() / 2, r.point(0).y };
}

Point s(const Rectangle& r)
{
	return { r.point(0).x + r.width() / 2, r.point(0).y + r.height() };
}

Point e(const Rectangle& r)
{
	return { r.point(0).x + r.width(), r.point(0).y + r.height() / 2 };
}

Point w(const Rectangle& r)
{
	return { r.point(0).x, r.point(0).y + r.height() / 2 };
}

Point center(const Rectangle& r)
{
	return { r.point(0).x + r.width() / 2, r.point(0).y + r.height() / 2 };
}

Point ne(const Rectangle& r)
{
	return { r.point(0).x + r.width(), r.point(0).y };
}

Point se(const Rectangle& r)
{
	return { r.point(0).x + r.width(), r.point(0).y + r.height() };
}

Point sw(const Rectangle& r)
{
	return { r.point(0).x, r.point(0).y + r.height() };
}

Point nw(const Rectangle& r)
{
	return r.point(0);
}

string point_to_string(Point p)
{
	ostringstream oss;
	oss << '(' << p.x << ',' << p.y << ')';
	return oss.str();
}

Point n(const Circle& c)
{
	auto r = Rectangle{ {c.center().x - c.radius(), c.center().y - c.radius()}, c.radius() * 2, c.radius() * 2 };
	return n(r);
}

Point s(const Circle& c)
{
	auto r = Rectangle{ {c.center().x - c.radius(), c.center().y - c.radius()}, c.radius() * 2, c.radius() * 2 };
	return s(r);
}

Point e(const Circle& c)
{
	auto r = Rectangle{ {c.center().x - c.radius(), c.center().y - c.radius()}, c.radius() * 2, c.radius() * 2 };
	return e(r);
}

Point w(const Circle& c)
{
	auto r = Rectangle{ {c.center().x - c.radius(), c.center().y - c.radius()}, c.radius() * 2, c.radius() * 2 };
	return w(r);
}

Point center(const Circle& c)
{
	auto r = Rectangle{ {c.center().x - c.radius(), c.center().y - c.radius()}, c.radius() * 2, c.radius() * 2 };
	return center(r);
}

Point ne(const Circle& c)
{
	auto r = Rectangle{ {c.center().x - c.radius(), c.center().y - c.radius()}, c.radius() * 2, c.radius() * 2 };
	return ne(r);
}

Point se(const Circle& c)
{
	auto r = Rectangle{ {c.center().x - c.radius(), c.center().y - c.radius()}, c.radius() * 2, c.radius() * 2 };
	return se(r);
}

Point sw(const Circle& c)
{
	auto r = Rectangle{ {c.center().x - c.radius(), c.center().y - c.radius()}, c.radius() * 2, c.radius() * 2 };
	return sw(r);
}

Point nw(const Circle& c)
{
	auto r = Rectangle{ {c.center().x - c.radius(), c.center().y - c.radius()}, c.radius() * 2, c.radius() * 2 };
	return nw(r);
}
////////
Point n(const Ellipse& el)
{
	auto r = Rectangle{ {el.center().x - el.major(), el.center().y - el.minor()}, el.major() * 2, el.minor() * 2 };
	return n(r);
}

Point s(const Ellipse& el)
{
	auto r = Rectangle{ {el.center().x - el.major(), el.center().y - el.minor()}, el.major() * 2, el.minor() * 2 };
	return s(r);
}

Point e(const Ellipse& el)
{
	auto r = Rectangle{ {el.center().x - el.major(), el.center().y - el.minor()}, el.major() * 2, el.minor() * 2 };
	return e(r);
}

Point w(const Ellipse& el)
{
	auto r = Rectangle{ {el.center().x - el.major(), el.center().y - el.minor()}, el.major() * 2, el.minor() * 2 };
	return w(r);
}

Point center(const Ellipse& el)
{
	auto r = Rectangle{ {el.center().x - el.major(), el.center().y - el.minor()}, el.major() * 2, el.minor() * 2 };
	return center(r);
}

Point ne(const Ellipse& el)
{
	auto r = Rectangle{ {el.center().x - el.major(), el.center().y - el.minor()}, el.major() * 2, el.minor() * 2 };
	return ne(r);
}

Point se(const Ellipse& el)
{
	auto r = Rectangle{ {el.center().x - el.major(), el.center().y - el.minor()}, el.major() * 2, el.minor() * 2 };
	return se(r);
}

Point sw(const Ellipse& el)
{
	auto r = Rectangle{ {el.center().x - el.major(), el.center().y - el.minor()}, el.major() * 2, el.minor() * 2 };
	return sw(r);
}

Point nw(const Ellipse& el)
{
	auto r = Rectangle{ {el.center().x - el.major(), el.center().y - el.minor()}, el.major() * 2, el.minor() * 2 };
	return nw(r);
}
#endif // !CIRCLE_CONNECTION_POINTS_HPP
