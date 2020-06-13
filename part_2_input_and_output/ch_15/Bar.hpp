#ifndef BAR_HPP
#define BAR_HPP
#include <graphics/Graph.h>

class Bar : public Graph_lib::Shape
{
public:
	Bar(const Graph_lib::Point& bl, const vector<double>& values, int xscale = 25, int yscale = 25, const string& lbl = "");
	void draw_lines() const;
	void set_fill_color(size_t pos, Graph_lib::Color col);
	void set_label(size_t pos, const string& lbl, Graph_lib::Color col = 0);
	void set_label(const string& lbl, Graph_lib::Color col = 0);
	size_t num_of_bars() const;
private:
	vector<double> m_values;
	vector<Graph_lib::Rectangle> m_bars;
	vector<Graph_lib::Text> m_labels;
	int m_xscale;
	int m_yscale;
	Graph_lib::Point m_bl;
	Graph_lib::Text m_lbl = Graph_lib::Text(Graph_lib::Point(), "");
	int m_graph_title_size = 14;
private:
	Graph_lib::Text* find_text(const string& lbl);
};
#endif // !BAR_HPP
