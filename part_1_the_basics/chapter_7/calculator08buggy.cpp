/*
	Simple calculator

	Originally written by Bjarne Stroustrup
		(bs@cs.tamu.edu) Spring 2004.

	This program implements a basic calculator.
	Input from cin; output to cout.
	The grammar for input is:

	Statement:
		Expression
		Print
		Quit
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
		sqrt( Primary )
	Number:
		floating-point-literal
*/

#include "std_lib_facilities.h"

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

const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char square_root = 'R';

// Returns a Token from buffers if it is not empty or gets a Token from std::cin
Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
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
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) 
				s += ch;
			cin.unget();
			if (s == "let") 
				return Token(let);
			if (s == "quit") 
				return Token(quit);
			if (s == "sqrt")
				return Token(square_root);
			return Token(name, s);
		}
		error("Bad token");
	}
}

// Skips characters in Token_stream until c
void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable
{
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

// Holds declared variables
vector<Variable> names;

// Returns value of variable by it's name
double get_value(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

// Updates values of variable
void set_value(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

// Checks whether variable with name s is declared
bool is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

void define_name(const string& name, double value)
{
	if (is_declared(name))
		error("redeclaration of variable");
	names.push_back(Variable(name, value));
}

// Holds stream of token.
Token_stream ts;

double expression(); // forward declaration for usage in primary() function

// Handles '(' Expression ')'
// - Primary
// Variable
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
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
		auto d = primary();
		if (d < 0)
			error("square root is defined for non negative numbers");
		return sqrt(d);
	}
	case name:
	{
		auto prevToken = t;
		t = ts.get();
		if (t.kind != '=')
		{
			ts.unget(t);
			return get_value(prevToken.name);
		}
		set_value(prevToken.name, expression());
		return get_value(prevToken.name);
	}
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
double declaration()
{
	Token t = ts.get();
	if (t.kind != 'a') error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	names.push_back(Variable(name, d));
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
			if (t.kind == quit) 
				return;
			ts.unget(t);
			cout << result << statement() << endl;
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
	define_name("k", 1000);
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