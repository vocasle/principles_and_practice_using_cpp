/*
	Simple calculator

	Originally written by Bjarne Stroustrup
		(bs@cs.tamu.edu) Spring 2004.

	Possible extensions:
		1. Add logarithmic functions
		2. Add factorial function
		3. Add trigonometric functions

	This program implements a basic calculator.
	Input from cin; output to cout.
	The grammar for input is:

	Calculation:
		Statement
		Help
		Print
		Quit
		Calculation Statement
	Statement:
		Declaration
		Expression
	Declaration:
		"#" Name "=" Expression
		"const" Name "=" Expression
	Help
		"h"
		"H"
	Print
		;
	Quit
		q
	Expression:
		Term
		Expression + Term
		Expression - Term
	Term:
		Primary
		Term * Primary
		Term / Primary
		Term % Primary
	Primary:
		Number
		( Expression )
		- Primary
		+ Primary
		sqrt( Expression )
		pow( Expression, Expression )
		ln( Expression )
	Number:
		floating-point-literal
*/

#include "std_lib_facilities.h"

struct Variable
{
	string name;
	double value;
	bool is_const;
	Variable(string n, double v) :name(n), value(v), is_const(false) { }
	Variable(string n, double v, bool is_const) :name(n), value(v), is_const(is_const) { }
};

struct Token
{
	char kind;
	double value; // only for numbers
	string name; // only for let and variable names
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string n) : kind(ch), name(n), value(0) { }
};

class Token_stream
{
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

class Symbol_table
{
public:
	double get_value(const string& name);
	void set_value(const string& name, double value);
	bool is_declared(const string& name);
	void define_name(const string& name, double value, bool is_const);
private:
	vector<Variable> var_table{};
};

const char let = '#';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char square_root = 'R';
const char power = 'P';
const char constant = 'C';
const char help = 'H';
const char natural_log = 'N';

// Returns a Token from buffers if it is not empty or gets a Token from std::cin
Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	ch = cin.get();
	switch (ch)
	{
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case ',':
	case '=':
	case '#':
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		cin.unget(); // put back character to read full double later
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
		if (isalpha(ch))
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
				s += ch;
			cin.unget();
			if (s == "exit")
				return Token(quit);
			if (s == "sqrt")
				return Token(square_root);
			if (s == "pow")
				return Token(power);
			if (s == "const")
				return Token(constant);
			if (s == "help")
				return Token(help);
			if (s == "ln")
				return Token(natural_log);
			return Token(name, s);
		}
		else if (isspace(ch))
		{
			if (ch == '\n')
				return Token(print);
			return get();
		}
		error("Bad token");
	}
}

// Skips characters in Token_stream until c
void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;

	char ch;
	while (true)
	{
		ch = cin.get();
		if (ch == c || ch == '\n') 
			return;
	}
}

// Returns value of variable by it's name
double Symbol_table::get_value(const string& s)
{
	for (auto&& var : var_table)
		if (var.name == s)
			return var.value;
	error("get: undefined name ", s);
}

// Updates values of variable
void Symbol_table::set_value(const string& s, double d)
{
	for (auto&& var : var_table)
		if (var.name == s)
		{
			if (var.is_const)
				error("value of constant cannot be changed");
			var.value = d;
			return;
		}
	error("set: undefined name ", s);
}

// Checks whether variable with name s is declared
bool Symbol_table::is_declared(const string& s)
{
	for (auto&& var : var_table)
		if (var.name == s)
			return true;
	return false;
}

void Symbol_table::define_name(const string& name, double value, bool is_const = false)
{
	if (is_declared(name))
		error("redeclaration of variable");
	var_table.push_back(Variable(name, value, is_const));
}

// Holds stream of token.
Token_stream ts;
// Holds set of variables
Symbol_table st;

double expression(); // forward declaration for usage in primary() function

// Handles '(' Expression ')'
// - Primary
// Variable
double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
		return d;
	}
	case '-':
		return -primary();
	case '+':
		return primary();
	case number:
		return t.value;
	case square_root:
	{
		auto d = expression();
		if (d < 0)
			error("square root is defined for non negative numbers");
		return sqrt(d);
	}
	case power:
	{
		t = ts.get();
		if (t.kind != '(')
			error("'(' expected after pow");
		double base = expression();
		t = ts.get();
		if (t.kind != ',')
			error("',' expected");
		auto exponent = expression();
		if (static_cast<int32_t>(exponent) != exponent)
			error("exponent for pow function must be an iteger");
		t = ts.get();
		if (t.kind != ')')
			error("')' expected");
		return pow(base, exponent);
	}
	case name:
	{
		auto prevToken = t;
		t = ts.get();
		if (t.kind != '=')
		{
			ts.unget(t);
			return st.get_value(prevToken.name);
		}
		st.set_value(prevToken.name, expression());
		return st.get_value(prevToken.name);
	}
	case natural_log:
		return log(primary());
	default:
		error("primary expected");
	}
}

// Handles multiplication and division
double term()
{
	double left = primary();
	while (true)
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case '*':
			left *= primary();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			auto d = primary();
			if (d == 0)
				error("divide by zero");
			left = fmod(left, d);
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}
// Handles summation and subtraction operations
double expression()
{
	double left = term();
	while (true)
	{
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}
// Handles declaration of new variables
double declaration(bool is_const = false)
{
	Token t = ts.get();
	if (t.kind != 'a') error("name expected in declaration");
	string name = t.name;
	if (st.is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	st.define_name(name, d, is_const);
	return d;
}
// Handles declarations of new variables and expressions
double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration();
	case constant:
		return declaration(true);
	default:
		ts.unget(t);
		return expression();
	}
}
// Restores the program state after encountering an error input
void clean_up_mess()
{
	ts.ignore(print);
}

void print_help();

const string prompt = "> ";
const string result = "= ";
// Calculation loop. It allows to calculate several expression on one line
void calculate()
{
	while (true)
	{
		try
		{
			cout << prompt;
			Token t = ts.get();
			while (t.kind == print)
				t = ts.get();
			switch (t.kind)
			{
			case help:
				print_help();
				break;
			case quit:
				return;
			default:
				ts.unget(t);
				cout << result << statement() << endl;
			}
		}
		catch (runtime_error& e)
		{
			cerr << e.what() << endl;
			clean_up_mess();
		}
	}
}

int main()
{
	st.define_name("k", 1000);
	try
	{
		calculate();
		return 0;
	}
	catch (exception& e)
	{
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >> c && c != ';');
		return 1;
	}
	catch (...)
	{
		cerr << "exception\n";
		char c;
		while (cin >> c && c != ';');
		return 2;
	}
}

void print_help()
{
	cout << "Enter an expression and press 'enter' to get a result, e.g.\n"
		<< "> 2 + 5 * (3 * 2) / 10.5 * 3.14 % 3\n"
		<< "= 4.97143\n\n"
		<< "Supported operations are: '+', '-', '*', '/', '%'\n\n"
		<< "'%' returns remainder from division, e.g. 5 % 2 = 1\n\n"
		<< "Calculator supports real numbers and integers. You can input real numbers in\n"
		<< "scientific notation, e.g. 1e6, 1e-6\n\n"
		<< "It is possible to define constants to use them later.\n"
		<< "Example of definition:\n"
		<< "> const pi = 3.14\n"
		<< "To use defined constant later - type it's name in expression.\n"
		<< "You can calculate area of circle with radius equal to 5.3 using defined constant 'pi':\n"
		<< "> pi * 5.3 * 5.3\n"
		<< "= 88.2026\n\n"
		<< "It is possible to define variables to use them later.\n"
		<< "Example of definition:\n"
		<< "# radius = 5.3\n"
		<< "To calculate area of circle you with radius equal 5.3:\n"
		<< "> # area = pi * radius * radius\n"
		<< "= 88.2026\n\n"
		<< endl;
}