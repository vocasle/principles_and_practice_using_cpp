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

int main()
{
	auto win = Simple_window(Point(100, 100), 800, 600, "Exercise 1");
	auto smiley = SmileyFace(Point(100, 100), 50);
	auto frowny = FrownyFace(Point(200, 100), 50);
	win.attach(smiley);
	win.attach(frowny);
	win.wait_for_button();
}