#include <vector>
#include <string>

class Name_pairs
{
public:
	void read_names();
	void read_ages();
	void print();
	void sort();
private:
	std::vector<std::string> name;
	std::vector<double> age;
};

std::string trim(const std::string& s);
void error(const std::string& msg);