#include "Pseudo_window.hpp"

Pseudo_window::Pseudo_window(const Point& tl, uint32_t width, uint32_t height, const string& title) 
	: Rectangle{tl, width, height},
	m_width{width}, m_height{height},
	m_title({tl.x + 7, tl.y + 14}, title),
	m_header{ tl, width, 20 },
	m_close{{tl.x + static_cast<int>(width) - 20, tl.y}, 20, 20},
	m_maximize{ {tl.x + static_cast<int>(width) - 40, tl.y}, 20, 20 },
	m_minimize{ {tl.x + static_cast<int>(width) - 60, tl.y}, 20, 20 }
{
	m_header.set_fill_color(Color::white);
	m_close.set_fill_color(Color::red);
	m_minimize.set_fill_color(Color::magenta);
	m_maximize.set_fill_color(Color::blue);
	m_close.set_color(Color::invisible);
	m_maximize.set_color(Color::invisible);
	m_minimize.set_color(Color::invisible);
}

void Pseudo_window::set_title(const string& title)
{
	m_title.set_label(title);
}

void Pseudo_window::draw_lines() const
{
	if (m_image)
	{
		auto p = Rectangle::point(0);
		m_image->set_mask({p.x, p.y + m_header.height()}, m_width, m_height);
		m_image->draw_lines();
	}
	Rectangle::draw_lines();
	m_header.draw_lines();
	m_close.draw_lines();
	m_maximize.draw_lines();
	m_minimize.draw_lines();
	m_title.draw_lines();
}
