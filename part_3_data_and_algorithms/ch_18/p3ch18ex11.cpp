// A naive implementation of SkipList data structure

#include <limits>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cassert>
#include <sstream>

typedef std::string Elem;


#ifndef NDEBUG
static int ALLOCATIONS = 0;

void* operator new(size_t count)
{
	ALLOCATIONS++;
	return std::malloc(count);
}

void operator delete(void* ptr)
{
	ALLOCATIONS--;
	free(ptr);
}
#endif // !NDEBUG


class SkipList
{
public:
	struct Node
	{
		Node* prev = nullptr;
		Node* next = nullptr;
		Node* top = nullptr;
		Node* bot = nullptr;
		Elem val;
		int key;
		Node(int inKey, const Elem& inVal);
	};
public:
	SkipList();
	~SkipList();
	Node* Find(int key) const;
	Node* Insert(int key, const Elem& val);
	void Remove(int key);
	int Height() const;
	int Size() const;
	bool IsEmpty() const;
	void Print() const;
private:
	Node* header;
	Node* trailer;
	int size;
	int height;
	static constexpr int HEADER_KEY = std::numeric_limits<int>::min();
	static constexpr int TRAILER_KEY = std::numeric_limits<int>::max();
	static constexpr const char* HEADER_VAL = "HEADER";
	static constexpr const char* TRAILER_VAL = "TRAILER";
private:
	int GetLevel() const;
	std::vector<Node*> GetUpperNodes(const int inKey) const;
};

typedef SkipList::Node Node;

int main()
{
	{
		SkipList list;
		for (int i = 0; i < 10; i++)
		{
			Node* n = list.Insert(i, "NEW_NODE" + std::to_string(i));
			assert((n != nullptr) &&  "inserted node is null");
			assert((n == list.Find(i)) && "could not find inserted node");
		}
		
		for (int i = 9; i >= 0; i--)
		{
			list.Remove(i);
			std::ostringstream buf;
			buf << "Node with key=" << i << " was not deleted!";
			assert((list.Find(i) == nullptr) && buf.str().c_str());
			std::cout << "list.Size()=" << list.Size() << "\n";
		}
	}
	assert((ALLOCATIONS == 0) && "Memory leak detected");
	std::cin.get();
}

SkipList::Node::Node(int inKey, const Elem& inVal) :
	key(inKey),
	val(inVal)
{}

SkipList::SkipList() :
	header(new Node(HEADER_KEY, HEADER_VAL)),
	trailer(new Node(TRAILER_KEY, TRAILER_VAL)),
	size(0),
	height(1)
{
	header->next = trailer;
	trailer->prev = header;
}

SkipList::~SkipList()
{
	Node* top = header;
	while(top)
	{
		Node* node = top;
		top = top->bot;
		while (node)
		{
			Node* tmp = node;
			node = node->next;
			delete tmp;
		}
	}
}

Node* SkipList::Find(int inKey) const
{
	int lvl = height;
	Node* p = header->next;
	while (lvl-- >= 0)
	{
		while (p)
		{
			if (p->key < inKey && p->next)
			{
				p = p->next;
			}
			else if (p->key == inKey)
			{
				return p;
			}
			else
			{
				p = p->prev->bot;
				break;
			}
		}
	}
	return nullptr;
}

Node* SkipList::Insert(int inKey, const Elem& inVal)
{
	Node* found = Find(inKey);
	if (found)
	{
		found->val = inVal;
		return found;
	}
	
	std::vector<Node*> upperNodes = GetUpperNodes(inKey);
	int lvl = GetLevel();
	Node* prev = nullptr;
	bool shouldAddLvl = lvl > upperNodes.size();
	int lastIdx = shouldAddLvl ? 0 : upperNodes.size() - lvl;
	
	for (int idx = upperNodes.size() - 1; idx >= lastIdx; idx--)
	{
		Node* upper = upperNodes[idx];
		Node* node = new Node(inKey, inVal);
		upper->next->prev = node;
		node->next = upper->next;
		upper->next = node;
		node->prev = upper;
		if (prev)
		{
			node->bot = prev;
			prev->top = node;
		}
		prev = node;

		assert((node->next != nullptr) && "new node does not have next");
		assert((node->prev != nullptr) && "new node does not have prev");
		if (idx == upperNodes.size() - 1)
		{
			assert((upper->bot == nullptr) && "inserting not in bottom");
		}
	}

	if (shouldAddLvl)
	{
		lvl -= upperNodes.size(); // that much levels were already added
		while(lvl--)
		{
			assert((prev) && "prev is NULL");
			Node* node = new Node(inKey, inVal);
			node->bot = prev;
			prev->top = node;

			Node* nHead = new Node(header->key, header->val);
			nHead->bot = header;
			header->top = nHead;
			nHead->next = node;
			node->prev = nHead;
			header = nHead;

			Node* nTail = new Node(trailer->key, trailer->val);
			nTail->bot = trailer;
			trailer->top = nTail;
			nTail->prev = node;
			node->next = nTail;
			trailer = nTail;

			assert((header->bot != nullptr) && "header is not connected to bot node");
			assert((trailer->bot != nullptr) && "trailer is not connected to bot node");

			prev = node;
			++height;
		}
	}
	
	++size;
	return prev && prev->top ? prev->top : prev;
}

void SkipList::Remove(int inKey)
{
	Node* node = Find(inKey);
	if (node)
	{
		assert((node->top == nullptr) && "Found node is not at the top level!");
		if (node->key == TRAILER_KEY || node->key == HEADER_KEY)
		{
			return;
		}
		while(node)
		{
			Node* nodeCopy = node;
			node->prev->next = node->next;
			node->next->prev = node->prev;
			node = node->bot;
			delete nodeCopy;
		}
		--size;
	}
}

int SkipList::GetLevel() const
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::bernoulli_distribution dist;
	int lvl = 1;
	while(dist(gen))
	{
		++lvl;
	}
	return lvl;
}

std::vector<Node*> SkipList::GetUpperNodes(const int inKey) const
{
	Node* node = header->next;
	int lvl = height;
	std::vector<Node*> upperNodes;
	upperNodes.reserve(height);
	while (lvl-- != 0)
	{
		while (node)
		{
			if (node->key < inKey && node->next)
			{
				node = node->next;
			}
			else
			{
				upperNodes.push_back(node->prev);
				node = node->prev->bot;
				break;
			}
		}
	}

	assert((height == upperNodes.size()) && "upperNodes contains more nodes than height of list");

	return upperNodes;
}

int SkipList::Height() const
{
	return height;
}

int SkipList::Size() const
{
	return size;
}

bool SkipList::IsEmpty() const
{
	return size == 0;
}

void SkipList::Print() const
{
	Node* head = header;
	int lvl = height;
	while(head)
	{
		std::cout << "\n[" << lvl << "] - ";
		Node* node = head;
		while(node)
		{
			std::cout << "{ " << node->key << " " << node->val << " }";
			if (node->next)
			{
				std::cout << ", ";
			}
			node = node->next;
		}
		std::cout << "\n";
		head = head->bot;
		lvl--;
	}
}
