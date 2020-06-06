#include <iostream>
#include <graphics/Graph.h>
#include <graphics/Simple_window.h>

// The third application of a Controller is turning on and off the logging or assertions.

class Controller
{
public:
	virtual void on() = 0;
	virtual void off() = 0;
	virtual void set_level(int) = 0;
	virtual void show() const = 0;
};

class ControllerTest : public Controller
{
public:
	void on() override { is_on = true; }
	void off() override { is_on = false; }
	void set_level(int new_lvl) override { lvl = new_lvl; }
	void show() const override { std::cout << "state: " << (is_on ? "on" : "off") << ", lvl: " << lvl << std::endl; }
private:
	bool is_on = true;
	int lvl = 0;
};

class ShapeController : public Controller
{
public:
	ShapeController(Graph_lib::Shape* s) : s{ s }, color{ &s->color() } {}
	void on() override { s->set_color(Graph_lib::Color::red); }
	void off() override { s->set_color(*color); }
	void set_level(int lvl) override { s->set_style(Graph_lib::Line_style(lvl)); this->lvl = lvl; }
	void show() const override { std::cout << "color: " << s->color().as_int() << " line width: " << lvl << std::endl; }
private:
	Graph_lib::Shape* s;
	int lvl = 0;
	Graph_lib::Color* color;
};

int main()
{
	ControllerTest ct{};
	ct.off();
	ct.set_level(1);
	ct.show();

	Simple_window win{ {100, 100}, 800, 600, "Exercise 16" };

	Graph_lib::Circle c{ {100, 100}, 50 };
	win.attach(c);
	ShapeController sc{ &c };
	sc.show();
	sc.off();
	sc.set_level(10);
	sc.show();
	std::cout << "color: " << c.color().as_int() << std::endl;
	win.wait_for_button();
}