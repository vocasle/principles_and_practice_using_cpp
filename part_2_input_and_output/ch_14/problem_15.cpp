#include <vector>
#include <list>
#include <iostream>

class Iterator
{
public:
	virtual double* next() = 0;
};

class VectorIterator : public Iterator
{
public:
	VectorIterator(std::vector<double>& v) : it{ v.begin() }, end{ v.end() } {}
	double* next() override
	{
		if (it == end)
			return nullptr;
		return &*it++;
	}
private:
	std::vector<double>::iterator it;
	std::vector<double>::iterator end;
};

class ListIterator : public Iterator
{
public:
	ListIterator(std::list<double>& l) : it{ l.begin() }, end{ l.end() } {}
	double* next() override
	{
		if (it == end)
			return nullptr;
		return &*it++;
	}
private:
	std::list<double>::iterator it;
	std::list<double>::iterator end;
};

void print(Iterator& it)
{
	for (double* d = it.next(); d != nullptr; d = it.next())
	{
		std::cout << *d << ' ';
	}
	std::cout << std::endl;
}

int main()
{
	std::vector<double> vec{ 1.2,2.3,3.4,4.5,5.6,6.7,7.8,8.9 };
	std::list<double> lst{ 1.2,2.3,3.4,4.5,5.6,6.7,7.8,8.9 };
	VectorIterator vit{ vec };
	ListIterator lit{ lst };
	print(vit);
	print(lit);
}