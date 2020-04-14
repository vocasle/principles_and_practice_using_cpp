#include <fstream>
#include <iostream>
#include <string>

float read_int(std::istream& is)
{
	float num{ 0 };
	is >> num;
	if (!is)
	{
		if (!is.eof())
		{
			is.clear();
			is.unget();
			std::string line;
			std::getline(is, line);
			throw std::runtime_error("'" + line + "' is not a valid number.");
		}
	}
	return num;
}

float sum(const std::string& file_name)
{
	std::ifstream ifs{ file_name };
	if (!ifs)
	{
		throw std::runtime_error("Could not open '" +
			file_name + "' for reading.");
	}
	ifs.exceptions(ifs.exceptions()|std::ios_base::badbit);
	float sum{ 0 };
	try
	{
		while (!ifs.eof())
		{
			sum += read_int(ifs);
		}
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("Found bad symbol in file '" + file_name
			+ "'. " + e.what());
	}
	return sum;
}

int main()
{
	auto file_name = "numbers.txt";
	try
	{
		auto num_sum = sum(file_name);
		std::cout << "Sum of all numbers in '" << file_name << "' is: "
			<< num_sum << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}