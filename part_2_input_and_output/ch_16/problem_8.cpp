#include <graphics/Window.h>
#include <graphics/GUI.h>
#include <set>

using namespace Graph_lib;

typedef string UnitOfMeasure;

struct Currency
{
	double value;
	UnitOfMeasure uom;
	Currency(double value, UnitOfMeasure uom) : value{ value }, uom{ uom } {}
	Currency() : value{ 0.0 } {}
};

istream& operator>>(istream& is, Currency& c);

class CurrencyConverter
{
public:
	CurrencyConverter();
	Currency convert(const Currency& from, const Currency& to) const;
	void load_rates(const string& file_name);
	const vector<UnitOfMeasure>& get_uoms() const;
	set<UnitOfMeasure> defined_conversions_for(const UnitOfMeasure& uom);
private:
	vector<pair<Currency, Currency>> currencies;
	vector<UnitOfMeasure> uoms;
	bool is_uom_known(const UnitOfMeasure& uom);
};

class MyWindow : public Window
{
public:
	MyWindow(Point xy, int w, int h, const string& label)
		: Window(xy, w, h, label),
		file_name{{120,20}, 150, 20, "currency rates:"},
		btn_load_rates{ {280, 20}, 70, 20, "load", [](Address, Address pw) {
			reference_to<MyWindow>(pw).conv.load_rates(reference_to<MyWindow>(pw).file_name.get_string());
			reference_to<MyWindow>(pw).construct_ui();
		} },
		from{{170, 60}, 100, 20, "from:"},
		to{{350, 60}, 100, 20, "to:"},
		btn_convert{ {495, 60}, 70, 20, "convert", [](Address, Address pw) {
			reference_to<MyWindow>(pw).convert();
		} },
		menu_from{{170, 80}, 100, 20, Menu::vertical, "currency"},
		menu_to{ {350, 80}, 100, 20, Menu::vertical, "currency" },
		uom_from{{280, 75}, ""},
		uom_to{{460, 75}, ""}
	{
		attach(file_name);
		attach(btn_load_rates);
		attach(from);
		attach(to);
		attach(btn_convert);
		attach(uom_from);
		attach(uom_to);
		btn_convert.hide();
		uom_from.set_color(Color::black);
		uom_to.set_color(Color::black);
	}
	void hide_undefined_conversions(const UnitOfMeasure& uom);
	void convert();
private:
	In_box file_name;
	Button btn_load_rates;
	CurrencyConverter conv;
	In_box from;
	Out_box to;
	Menu menu_from;
	Menu menu_to;
	Button btn_convert;
	Text uom_from;
	Text uom_to;
	void construct_ui();
};


int main()
try
{
	MyWindow win{ {100, 100}, 800, 600, "Exercise 8" };
	return gui_main();
}
catch (exception& e)
{
	cerr << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "Unhandled exception\n";
	return 2;
}

CurrencyConverter::CurrencyConverter()
{
	
}

void CurrencyConverter::load_rates(const string& file_name)
{
	if (file_name.empty())
		error("Invalid filename provided");
	ifstream file{ file_name };
	if (!file)
		error("Could not open file: ", file_name);
	for (std::string line; getline(file, line);)
	{
		Currency from;
		Currency to;
		char delim = 0;
		istringstream is{ line };
		if (is >> from >> delim >> to)
		{
			currencies.emplace_back(from, to);
			if (!is_uom_known(from.uom))
				uoms.push_back(from.uom);
			if (!is_uom_known(to.uom))
				uoms.push_back(to.uom);
		}
		else
			error("Wrong formatting of the currencies: ", line);
	}
}

const vector<UnitOfMeasure>& CurrencyConverter::get_uoms() const
{
	return uoms;
}

set<UnitOfMeasure> CurrencyConverter::defined_conversions_for(const UnitOfMeasure& uom)
{
	set<UnitOfMeasure> defined_conversions;
	for (pair<Currency, Currency> currency_pair : currencies)
	{
		if (currency_pair.first.uom == uom)
			defined_conversions.insert(currency_pair.second.uom);
		if (currency_pair.second.uom == uom)
			defined_conversions.insert(currency_pair.first.uom);
	}
	return defined_conversions;
}

Currency CurrencyConverter::convert(const Currency& from, const Currency& to) const
{
	for (const pair<Currency, Currency> currency_pair : currencies)
	{
		if (currency_pair.first.uom == from.uom && currency_pair.second.uom == to.uom)
		{
			double target_value = currency_pair.second.value * from.value;
			return { target_value, currency_pair.second.uom };
		}
		if (currency_pair.second.uom == from.uom && currency_pair.first.uom == to.uom)
		{
			double target_value = from.value / currency_pair.second.value;
			return { target_value, currency_pair.first.uom };
		}
	}
}

bool CurrencyConverter::is_uom_known(const UnitOfMeasure& uom)
{
	return find(uoms.begin(), uoms.end(), uom) != uoms.end();
}

istream& operator>>(istream& is, Currency& c)
{
	double d = 0.0;
	string uom;
	if (is >> d >> uom)
	{
		if (d >= 0)
		{
			c.value = d;
			c.uom = uom;
		}
		else
			is.clear(ios::failbit);
	}
	return is;
}

void MyWindow::hide_undefined_conversions(const UnitOfMeasure& uom)
{
	set<UnitOfMeasure> defined_conversions = conv.defined_conversions_for(uom);
	for (int n = 0; n < menu_to.selection.size(); ++n)
	{
		if (defined_conversions.find(menu_to.selection[n].label) == defined_conversions.end())
			menu_to.selection[n].hide();
		else
			menu_to.selection[n].show();
	}
}

void MyWindow::convert()
{
	double value_from = 0.0;
	istringstream is{ from.get_string() };
	if (!(is >> value_from))
		error("Invalid number entered in 'from': ", from.get_string());
	
	Currency converted = conv.convert({ value_from, uom_from.label() }, { 1.0, uom_to.label() });
	to.put(to_string(converted.value));
}

void MyWindow::construct_ui()
{
	for (const UnitOfMeasure& uom : conv.get_uoms())
	{
		menu_from.attach(new Button{ {0,0},0,0, uom, [](Address pb, Address pw) {
			string label = reference_to<Fl_Button>(pb).label();
			reference_to<MyWindow>(pw).uom_from.set_label(label);
			reference_to<MyWindow>(pw).hide_undefined_conversions(label);
			reference_to<MyWindow>(pw).uom_to.set_label("");
			reference_to<MyWindow>(pw).btn_convert.hide();
			reference_to<MyWindow>(pw).redraw();
		} });
		menu_to.attach(new Button{ {0,0},0,0, uom, [](Address pb, Address pw) {
			string label = reference_to<Fl_Button>(pb).label();
			reference_to<MyWindow>(pw).uom_to.set_label(label);
			reference_to<MyWindow>(pw).btn_convert.show();
			reference_to<MyWindow>(pw).redraw();
		} });
	}
	attach(menu_from);
	attach(menu_to);
	redraw();
}
