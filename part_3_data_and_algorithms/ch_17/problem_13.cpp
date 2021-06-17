#include <string>
#include <stdexcept>
#include <iostream>

void error(const std::string& m)
{
	throw std::runtime_error(m);
}

struct God
{
	std::string m_name;
	std::string m_mythology;
	std::string m_vehicle;
	std::string m_weapon;
	God(const std::string& name, const std::string& mythology, const std::string& vehicle, const std::string& weapon) :
		m_name{ name }, m_mythology{ mythology }, m_vehicle{ vehicle }, m_weapon{ weapon }
	{
		if (name.empty() || mythology.empty() || m_weapon.empty())
			error("Either name or mythology or weapon is empty.");
	}
};

class Link
{
public:
	Link(const God& v, Link* p = nullptr, Link* s = nullptr);
	Link* insert(Link* n);
	Link* add(Link* n);
	Link* erase();
	Link* find(const std::string& s);
	const Link* find(const std::string& s) const;
	const Link* advance(int n) const;
	Link* next() const;
	Link* previous() const;
	Link* add_ordered(Link* n);
public:
	God value;
private:
	Link* prev;
	Link* succ;
};

void print_all(Link* p)
{
	std::cout << "{\n";
	while (p)
	{
		std::cout << "\t{ " << p->value.m_name << ", " << p->value.m_mythology
			<< ", " << p->value.m_vehicle << ", " << p->value.m_weapon << "}";
		p = p->next();
		if (p)
			std::cout << ",\n";
	}
	std::cout << "\n}";
}

int main()
{
	Link* norse_gods = new Link{ {"Freyja", "Norse", "", "Brísingamen"} };
	norse_gods = norse_gods->insert(new Link{ {"Odin", "Norse", "Sleipnir", "Gungnir"} });
	norse_gods = norse_gods->insert(new Link{ {"Loki", "Norse", "", "Change Shape"} });
	norse_gods = norse_gods->insert(new Link{{ "Thor", "Norse", "", "Mjollnir" }});
	print_all(norse_gods);
	std::cout << std::endl;

	Link* greek_gods = new Link{ {"Athena", "Greek", "", "Spear and Shield"} };
	greek_gods = greek_gods->insert(new Link{ {"Ares", "Greek", "", "Sword"} });
	greek_gods = greek_gods->insert(new Link{{"Zeus", "Greek", "", "Thunderbolt"} });
	greek_gods = greek_gods->insert(new Link{ {"Poseidon", "Greek", "" , "Trident"} });
	greek_gods = greek_gods->insert(new Link{ {"Cronus", "Greek", "", "Sickle"} });
	print_all(greek_gods);
	std::cout << std::endl;

	Link* roman_gods = new Link{ {"Neptune", "Roman", "", "Trident"} };
	roman_gods = roman_gods->insert(new Link{ {"Saturn", "Roman", "", "Time"} });
	roman_gods = roman_gods->insert(new Link{ {"Triton", "Roman", "", "Conch Shell"} });
	print_all(roman_gods);
	std::cout << std::endl;


	Link* p = norse_gods;
	Link* sorted_norse_gods = nullptr;
	while (p)
	{
		sorted_norse_gods = sorted_norse_gods->add_ordered(new Link{p->value});
		p = p->next();
	}

	print_all(sorted_norse_gods);
	std::cout << std::endl;

	p = greek_gods;
	Link* sorted_greek_gods = nullptr;
	while (p)
	{
		sorted_greek_gods = sorted_greek_gods->add_ordered(new Link{ p->value });
		p = p->next();
	}

	print_all(sorted_greek_gods);
	std::cout << std::endl;

	p = roman_gods;
	Link* sorted_roman_gods = nullptr;
	while (p)
	{
		sorted_roman_gods = sorted_roman_gods->add_ordered(new Link{ p->value });
		p = p->next();
	}

	print_all(sorted_roman_gods);
	std::cout << std::endl;
}


Link::Link(const God& v, Link* p, Link* s) : value{ v }, prev{ p }, succ{ s }
{
}

Link* Link::insert(Link* n)
{
	if (n == nullptr)
		return this;
	if (this == nullptr)
		return n;
	n->succ = this;
	if (prev)
		prev->succ = n;
	n->prev = prev;
	prev = n;
	return n;
}

Link* Link::add(Link* n)
{
	if (n == nullptr)
		return this;
	if (this == nullptr)
		return n;

	n->prev = this;
	if (succ)
		succ->prev = n;
	n->succ = succ;
	succ = n;
	return n;
}

Link* Link::erase()
{
	if (!this)
		return nullptr;
	if (succ)
		succ->prev = prev;
	if (prev)
		prev->succ = succ;
	return succ;
}

Link* Link::find(const std::string& s)
{
	Link* p = this;
	while (p)
	{
		if (p->value.m_name == s)
			return p;
		p = p->succ;
	}
	return nullptr;
}

const Link* Link::find(const std::string& s) const
{
	const Link* p = this;
	while (p)
	{
		if (p->value.m_name == s)
			return p;
		p = p->succ;
	}
	return nullptr;
}

const Link* Link::advance(int n) const
{
	const Link* p = this;
	if (!p)
		return nullptr;
	if (0 < n)
	{
		while (n--)
		{
			if (!p->succ)
				return nullptr;
			p = p->succ;
		}
	}
	else if (n < 0)
	{
		while (n++)
		{
			if (!p->prev)
				return nullptr;
			p = p->prev;
		}
	}
	return p;
}

Link* Link::next() const
{
	return succ;
}

Link* Link::previous() const
{
	return prev;
}

Link* Link::add_ordered(Link* n)
{
	Link* p = this;
	if (!n)
		return this;
	if (!p)
		return n;
	if (n->succ || n->prev)
		error("The node n must not have prev and succ!");

	while (p)
	{
		if (p->value.m_name > n->value.m_name)
		{
			if (p->prev)
				p = p->prev;
			else
			{
				p->prev = n;
				n->succ = p;
				return n;
			}
		}
		else
		{
			n->prev = p;
			n->succ = p->succ;
			if (p->succ)
				p->succ->prev = n;
			p->succ = n;
			return n;
		}
	}

    return n;
}
