// Singly linked list uses less memory, because the node stores only a pointer to the next node, but requires to traverse the list from the beginning if we need to find node in question
// Doubly linked list uses more memory, because the node stores two pointers - to the next node and to previous. Searching is more efficient because doubly linked list can be traversed in both directions

#include <iostream>
#include <string>
#include <stdexcept>

void error(const std::string& s)
{
	throw std::runtime_error(s);
}

struct Node
{
	Node* next;
	std::string value;
	Node(const std::string& v, Node* n = nullptr): value{v}, next{n} {}
};

class LinkedList
{
public:
	LinkedList();
	virtual ~LinkedList();
	void addFront(Node* n);
	void removeFront();
	Node* find(const std::string& s) const;
	Node* next();
	bool empty() const;
	size_t size() const;
private:
	size_t _size;
	Node* _head;
	Node* _next = nullptr;
};

int main()
{
	LinkedList norse_gods;
	norse_gods.addFront(new Node{ "Freyja" });
	norse_gods.addFront(new Node{ "Loki" });
	norse_gods.addFront(new Node{ "Odin" });
	norse_gods.addFront(new Node{ "Baldr" });
	norse_gods.addFront(new Node{ "Thor" });

	while (Node* n = norse_gods.next())
	{
		std::cout << "{ " << n->value << ", size: " << norse_gods.size() << " }\n";
		norse_gods.removeFront();
	}
	std::cout << norse_gods.size() << '\n';
}

LinkedList::LinkedList(): _size{0}, _head{nullptr}
{
}

LinkedList::~LinkedList()
{
	while (!empty())
		removeFront();
}

void LinkedList::addFront(Node* n)
{
	n->next = _head;
	_head = n;
	_next = _head;
	++_size;
}

void LinkedList::removeFront()
{
	if (empty())
		error("Cannot remove from the front, because LinkedList is empty");

	Node* p = _head;
	_head = _head->next;
	_next = _head;
	delete p;
	--_size;
}

Node* LinkedList::find(const std::string& s) const
{
	Node* p = _head;
	while (p)
	{
		if (p->value == s)
			return p;
	}
	return nullptr;
}

Node* LinkedList::next()
{
	Node* p = _next;
	_next = _next ? _next->next : _next;
	return p;
}


bool LinkedList::empty() const
{
	return _size == 0;
}

size_t LinkedList::size() const
{
	return _size;
}
