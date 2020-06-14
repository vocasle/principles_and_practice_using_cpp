#include "Bar.hpp"


Bar::Bar(const Graph_lib::Point& bl, const vector<double>& values, int xscale, int yscale , const string& lbl) :
	m_bl{ bl },
	m_values{ values },
	m_xscale{ xscale },
	m_yscale{ yscale },
	Graph_lib::Shape()
{
	int n = 0;
	for (const double& val : values)
	{
		int height = int(yscale * val);
		if (height < 0)
			m_bars.push_back(Graph_lib::Rectangle({ bl.x + xscale * n, bl.y }, xscale, -height));
		else
			m_bars.push_back(Graph_lib::Rectangle({ bl.x + xscale * n, bl.y - height }, xscale, height));
		++n;
	}
	m_lbl.move(bl.x + (xscale * values.size()) / 2, bl.y + m_graph_title_size);
	if (!lbl.empty())
		m_lbl.set_label(lbl);
}


void Bar::draw_lines() const
{
	for (const Graph_lib::Rectangle& bar : m_bars)
		bar.draw();
	for (const Graph_lib::Text& lbl : m_labels)
		lbl.draw();
	m_lbl.draw();
}
void Bar::set_fill_color(size_t pos, Graph_lib::Color col)
{
	if (pos >= m_bars.size())
		error(to_string(pos) + " is out of range");
	m_bars.at(pos).set_fill_color(col);
}
void Bar::set_label(size_t pos, const string& lbl, Graph_lib::Color col)
{
	if (pos >= m_bars.size())
		error(to_string(pos) + " is out of range");
	auto text = find_text(lbl);
	if (text)
	{
		text->set_label(lbl);
		text->set_color(col);
		return;
	}
	auto bar = m_bars.at(pos);
	Graph_lib::Text t{ {bar.point(0).x + bar.width() / 2, bar.point(0).y}, lbl };
	t.set_color(col);
	m_labels.push_back(t);
}
void Bar::set_label(const string& lbl, Graph_lib::Color col)
{
	m_lbl.set_label(lbl);
	m_lbl.set_color(col);
}
size_t Bar::num_of_bars() const { return m_bars.size(); }

Graph_lib::Text* Bar::find_text(const string& lbl)
{
	for (auto it = m_labels.begin(); it < m_labels.end(); ++it)
		if (it->label() == lbl)
			return it._Ptr;
	return nullptr;
}