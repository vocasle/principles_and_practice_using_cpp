#include <string>
#include <iostream>
#include <vector>

void error(const std::string& msg)
{
	throw std::runtime_error(msg);
}

bool is_valid_name(const std::string& name)
{
	bool is_valid = true;
	for (char ch : name)
		is_valid = is_valid && isalpha(ch);
	return is_valid;
}

bool is_valid_age(unsigned int age)
{
	return age < 150;
}

class Person
{
public:
	Person(const std::string& first_name, const std::string& last_name, unsigned int age): 
		m_first_name{first_name}, 
		m_last_name{last_name},
		m_age{age}
	{ 
		if (!is_valid_name(first_name) || !is_valid_name(last_name) || first_name.empty() || last_name.empty())
			error(first_name + " " + last_name + " is not a valid name");
		if (!is_valid_age(age))
			error(std::to_string(age) + " is not a valid age");
	}
	std::string first_name() const { return m_first_name; }
	std::string last_name() const { return m_last_name; }
	unsigned int age() const { return m_age; }
private:
	std::string m_first_name;
	std::string m_last_name;
	unsigned int m_age;
};

std::ostream& operator<<(std::ostream& os, const Person& p)
{
	os << "{first_name=" << p.first_name() << " last_name=" << p.last_name() << " age=" << p.age() << "}";
	return os;
}

bool read_name(std::istream& is, std::string& name)
{
	char ch = 0;
	while (is >> ch && isalpha(ch))
		name.push_back(ch);
	if (is.bad() || is.fail())
		return false;
	is.putback(ch);
	return true;
}

// {first_name=Nikita last_name=Elsakov age=25}
std::istream& operator>>(std::istream& is, Person& p)
{
	std::string name;
	std::string last_name;
	unsigned int age = 0;
	const std::string name_key{ "first_name=" };
	const std::string last_name_key{ " last_name=" };
	const std::string age_key{ " age=" };
	std::string key1(name_key.size(), ' ');
	std::string key2(last_name_key.size(), ' ');
	std::string key3(age_key.size(), ' ');
	std::string chars(2, ' ');

	if (is >> chars[0] && is.read(&key1[0], key1.size()) >> name
		&& is.read(&key2[0], key2.size()) >> last_name
		&& is.read(&key3[0], key3.size()) >> age >> chars[1])
	{
		if (chars[0] != '{' || key1 != name_key
			|| key2 != last_name_key 
			|| key3 != age_key
			|| chars[1] != '}')
		{
			is.clear(std::ios::failbit);
			return is;
		}
	}
	else
		return is;
	p = Person(name, last_name, age);
	return is;
}

std::vector<Person> read_persons(std::istream& is)
{
	std::vector<Person> persons;
	Person p{ "", "", 0 };
	while (is >> p)
		persons.push_back(p);
	return persons;
}

void print_persons(const std::vector<Person>& persons)
{
	for (const Person& p : persons)
		std::cout << p << '\n';
}

int main()
{
	try
	{
		Person p1 = Person("Goofy", "", 63);
		std::cout << p1;
		Person p2 = Person("", "", 0);
		std::cin >> p2;
		std::cout << p2;

		std::vector<Person> persons = read_persons(std::cin);
		print_persons(persons);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unknown exception.\n";
		return 2;
	}
}