#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

struct Contact
{
	std::string last_name;
	std::string first_name;
	std::string tel_num;
	std::string email;
	Contact(const std::string& last_name,
		const std::string& first_name,
		const std::string& tel_num,
		const std::string& email)
		: last_name{last_name},
		first_name{first_name},
		tel_num{tel_num},
		email{email} {}
};

void out_int_formatted(int i)
{
	std::cout << std::showbase;
	std::cout << std::dec << i << "\t(decimal)\n"
		<< std::oct << i << "\t(octal)\n"
		<< std::hex << i << "\t(hexadecimal)\n";
}

void test_input_modifiers()
{
	std::cout << "Enter four integers:\n";
	int a, b, c, d;
	std::cin >> a >> std::oct >> b >> std::hex >> c >> d;
	std::cout << std::dec;
	// outputs 1234    668     4660    4660
	// because input to a was read as decimal
	// input to b was read as octal
	// input to c and d was read as hexadecimal
	std::cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';
}

void out_double_formatted(double d)
{
	std::cout << std::defaultfloat << d << "\t(defaultfloat)\n"
		<< std::scientific << d << "\t(scientific)\n"
		<< std::fixed << d << "\t(fixed)\n";
}

void print_table()
{
	std::cout << "Enter your contacts in the format:\n"
		<< "<Last Name> <First Name> <Telephone Number> <Email Address>\n";
	std::string last_name, first_name, tel_num, email;
	std::vector<Contact> contacts;
	while (std::cin >> last_name >> first_name >> tel_num >> email)
	{
		contacts.emplace_back(last_name, first_name, tel_num, email);
	}

	for (auto& contact : contacts)
	{
		std::cout << '|' << std::setw(20) << contact.last_name
			<< " | " << std::setw(20) << contact.first_name
			<< " | " << std::setw(12) << contact.tel_num
			<< " | " << std::setw(20) << contact.email
			<< " |\n";
	}
}

int main()
{
	auto birth_year{ 1994 };
	out_int_formatted(birth_year);
	out_int_formatted(25);
	test_input_modifiers();
	out_double_formatted(1234567.89);
	print_table();
}