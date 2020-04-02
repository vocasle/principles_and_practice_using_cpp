#include <vector>
#include <string>

class Name_pairs
{
public:
	void read_names();
	void read_ages();
	void sort();
	const auto& get_name() const { return name; }
	const auto& get_age() const { return age; }
private:
	std::vector<std::string> name;
	std::vector<double> age;
};

std::string trim(const std::string& s);
void error(const std::string& msg);
std::ostream& operator<<(std::ostream& os, const Name_pairs& np);
bool operator==(const Name_pairs& lhs, const Name_pairs& rhs);
bool operator!=(const Name_pairs& lhs, const Name_pairs& rhs);