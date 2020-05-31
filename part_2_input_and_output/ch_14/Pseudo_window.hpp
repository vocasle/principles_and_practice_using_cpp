#ifndef PSEUDO_WINDOW_HPP
#define PSEUDO_WINDOW_HPP
#include <graphics/Graph.h>
using namespace Graph_lib;

class Pseudo_window : public Rectangle
{
public:
	Pseudo_window(const Point& tl, uint32_t width, uint32_t height, const string& title);
	string get_title() const { return m_title.label(); }
	uint32_t get_width() const { return m_width; }
	uint32_t get_height() const { return m_height; }
	void set_title(const string& title);
	void draw_lines() const;
	void attach(Image* img) { m_image = img; }
private:
	Text m_title;
	uint32_t m_width;
	uint32_t m_height;
	Rectangle m_header;
	Rectangle m_close;
	Rectangle m_minimize;
	Rectangle m_maximize;
	Image* m_image = nullptr;
};
#endif // !PSEUDO_WINDOW_HPP
