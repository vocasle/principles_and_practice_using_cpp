#include <string>
#include <iostream>

class Link
{
public:
	Link(const std::string& v, Link* p = nullptr, Link* s = nullptr);
	Link* insert(Link* n);
	Link* add(Link* n);
	Link* erase();
	Link* find(const std::string& s);
	const Link* find(const std::string& s) const;
	const Link* advance(int n) const;
	Link* next() const;
	Link* previous() const;
public:
	std::string value;
private:
	Link* prev;
	Link* succ;
};

void print_all(Link* p)
{
	std::cout << "{ ";
	while (p)
	{
		std::cout << p->value;
		p = p->next();
		if (p)
			std::cout << ", ";
	}
	std::cout << " }";
}

int main()
{
	Link* norse_gods = new Link{ "Thor" };
	norse_gods = norse_gods->insert(new Link{ "Odin" });
	norse_gods = norse_gods->insert(new Link{ "Zeus" });
	norse_gods = norse_gods->insert(new Link{ "Freia" });

	Link* greek_godes = new Link{ "Hera" };
	greek_godes = greek_godes->insert(new Link{ "Athena" });
	greek_godes = greek_godes->insert(new Link{ "Mars" });
	greek_godes = greek_godes->insert(new Link{ "Poseidon" });

	Link* p = greek_godes->find("Mars");
	if (p)
		p->value = "Ares";

	Link* p2 = norse_gods->find("Zeus");
	if (p2)
	{
		if (p2 == norse_gods)
			norse_gods = p2->next();
		p2->erase();
		greek_godes = greek_godes->insert(p2);
	}

	print_all(norse_gods);
	print_all(greek_godes);
}

Link::Link(const std::string& v, Link* p, Link* s) : value{ v }, prev{p}, succ{s}
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
		if (p->value == s)
			return p;
		p = p->succ;
	}
	return nullptr;
}

const Link* Link::find(const std::string& s) const
{
	const Link* l = find(s);
	return l;
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
