// Draws a series of superelipses.
// gen_points() function uses parametric equations, mentioned on Wikipedia
// https://en.wikipedia.org/wiki/Superellipse

#include <graphics/Simple_window.h>

// Determines wether str is a real number
// str - real number
bool is_double(const string& str)
{
	auto iss = istringstream{ str };
	auto d = 0.0;
	iss >> d;
	return !iss.fail() && iss.eof();
}

// Promts user for double input
double prompt_double(const string& str, istream& is, ostream& os)
{
	os << str;
	auto line = string();
	getline(is, line);
	if (!is_double(line))
	{
		error(line + " is not a double.");
	}
	return stod(line);
}

// Generate points of the superellipse
// N - number of points to draw
// Equation of superellipse
// | x / a |^m + | y / b |^n = 1; m,n > 0.
vector<Graph_lib::Point> gen_points(int N, double m, double n, double a, double b)
{
	using namespace Graph_lib;
	static constexpr auto pi = 3.14159265;
	// N is divided by 4 because in the loop we get 4 points
	const auto interval = (pi / 2) / (N / 4);
	auto points = vector<Point>();
	auto quadr1 = vector<Point>();
	auto quadr2 = vector<Point>();
	auto quadr3 = vector<Point>();
	auto quadr4 = vector<Point>();
	for (auto i = 0.0; i <= pi / 2; i += interval)
	{
		auto x = static_cast<int>(a * pow(cos(i), 2 / m));
		auto y = static_cast<int>(b * pow(sin(i), 2 / n));
		quadr1.push_back(Point{ x, y });
		quadr2.push_back(Point{ -x, y });
		quadr3.push_back(Point{ -x, -y });
		quadr4.push_back(Point{ x, -y });
	}
	points.insert(points.end(), quadr1.begin(), quadr1.end());
	points.insert(points.end(), quadr2.rbegin(), quadr2.rend());
	points.insert(points.end(), quadr3.begin(), quadr3.end());
	points.insert(points.end(), quadr4.rbegin(), quadr4.rend());
	return points;
}

// Generates a superellipse
// N - number of points to draw
// Equation of superellipse
// | x / a |^m + | y / b |^n = 1; m,n > 0.
Open_polyline gen_superellipse(double a, double b, double m, double n, int N)
{
	static constexpr auto pi = 3.14159265;
	using namespace Graph_lib;
	if (a == 0 || b == 0)
	{
		error("Division by zero is not defined. Parameter 'a' or 'b' is zero.");
	}
	if (!(m > 0 && n > 0))
	{
		error("Parameters 'm' and 'n' must be greater that zero.");
	}
	auto poly = Closed_polyline{};
	auto points = gen_points(N, m, n, a, b);

	for (auto& p : points)
	{
		// move point in respect to the center of the window
		p.x += 400;
		p.y += 300;
		poly.add(p);
	}
	return poly;
}

vector<Open_polyline> gen_ellipses(double a, double b, double m, double n, int N, const vector<Graph_lib::Color>& colors)
{
	auto ellipses = vector<Open_polyline>();
	auto col_pos = size_t(0);
	for (auto i = n, j = m; i < 3 && j < 3; i += 0.1, j += 0.1)
	{
		auto e = gen_superellipse(a, b, i, j, N);
		if (!colors.empty())
		{
			e.set_color(colors.at(col_pos));
			col_pos = col_pos + 1 == colors.size() ? 0 : col_pos + 1;
		}
		ellipses.push_back(e);
	}
	return ellipses;
}

int main()
{
	using namespace Graph_lib;
	try
	{
		std::cout << "This program draws series of superellipses.\n"
			<< "To learn more about superellipses consult Wikipedia:\n\n"
			<< "https://en.wikipedia.org/wiki/Superellipse\n\n"
			<< "Example of values for parameters:\n"
			<< "a = 300, b = 300, m = 0.1, n = 0.1, N = 100\n\n";
		auto a = prompt_double("Enter a: ", cin, cout);
		auto b = prompt_double("Enter b: ", cin, cout);
		auto m = prompt_double("Enter m: ", cin, cout);
		auto n = prompt_double("Enter n: ", cin, cout);
		auto N = prompt_double("Enter N: ", cin, cout);
		auto win = Simple_window{ Point{100, 100}, 800, 600, "Exercise 12" };
		auto ellipses = gen_ellipses(a, b, m, n, N, { Color::blue, Color::red, Color::green });
		for (auto& e : ellipses)
		{
			win.attach(e);
		}
		win.wait_for_button();
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "Unhandled error.\n";
		return 2;
	}
}