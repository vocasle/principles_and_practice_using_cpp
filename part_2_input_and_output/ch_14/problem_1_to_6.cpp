#include <graphics/Simple_window.h>

class Smiley : public Circle
{
public:
	using Circle::Circle;
};

class Frowny : public Circle
{
public:
	using Circle::Circle;
};

class SmileyFace : public Smiley
{
public:
	SmileyFace(Point c, int r): marks{"^^W"}, Smiley(c, r)
	{
		marks.add({ c.x - r / 2, c.y - r / 3 });
		marks.add({ c.x + r / 2, c.y - r / 3 });
		marks.add({ c.x, c.y + r / 2 });
	}

	void draw_lines() const
	{
		Smiley::draw_lines();
		marks.draw_lines();
	}
private:
	Marks marks;
};

class FrownyFace : public Frowny
{
public:
	FrownyFace(Point c, int r) : marks{ "**o" }, Frowny(c, r)
	{
		marks.add({ c.x - r / 2, c.y - r / 3 });
		marks.add({ c.x + r / 2, c.y - r / 3 });
		marks.add({ c.x, c.y + r / 2 });
	}

	void draw_lines() const
	{
		Frowny::draw_lines();
		marks.draw_lines();
	}
private:
	Marks marks;
};

class A
{
	void virtual a() = 0;
};

class Immobile_Circle : public Circle
{
public:
	using Circle::Circle;
	void move(int x, int y) {}
};

class Stripped_rectangle : public Rectangle
{
public:
	using Rectangle::Rectangle;
	void draw_lines() const
	{
		if (fill_color().visibility())
		{
			fl_color(fill_color().as_int());
			for (auto i = 0; i < height() / 2; i+=2)
			{
				fl_line(point(0).x, point(0).y + i, point(0).x + width(), point(0).y + i);
			}
			fl_color(color().as_int());	// reset color
		}
	}
};

class Stripped_circle : public Circle
{
public:
	using Circle::Circle;
	void draw_lines() const
	{
		static constexpr auto pi = 3.14159265359;
		if (fill_color().visibility())
		{
			fl_color(fill_color().as_int());
			for (auto i = pi / 2; i > 0; i -= pi / 45)
			{
				auto x = center().x + radius() * cos(i);
				auto y = center().y + radius() * sin(i);
				fl_line(x, y, center().x - (x - center().x), y);
				fl_line(x, center().y - (y - center().y), center().x - (x - center().x), center().y - (y - center().y));
			}
			fl_color(color().as_int());	// reset color
		}
	}
};

int main()
{
	auto win = Simple_window(Point(100, 100), 800, 600, "Exercise 1");
	auto smiley = SmileyFace(Point(100, 100), 50);
	auto frowny = FrownyFace(Point(200, 100), 50);
	win.attach(smiley);
	win.attach(frowny);

	auto c = Immobile_Circle(Point(400, 300), 50);
	win.attach(c);
	c.move(100, 100);

	auto rect = Stripped_rectangle(Point(600, 100), 100, 50);
	rect.set_fill_color(Color::red);
	win.attach(rect);

	auto circle = Stripped_circle(Point(700, 500), 50);
	circle.set_fill_color(Color::blue);
	win.attach(circle);
	
	win.wait_for_button();
}