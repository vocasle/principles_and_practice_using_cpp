// This program calculates all whitespace-separated integers in a file

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> read_file(const std::string& name)
{
	std::ifstream file{ name };
	if (!file)
	{
		throw std::runtime_error("Could not open '" + name + "' for reading.");
	}
	std::vector<std::string> words;
	std::string word;
	while (file >> word)
	{
		words.push_back(word);
	}
	return words;
}

bool is_number(const std::string& str)
{
	bool is_number{ true };
	for (auto& ch : str)
	{
		is_number = is_number && std::isdigit(ch);
	}
	return is_number;
}

long sum(const std::vector<std::string>& words)
{
	long sum{ 0 };
	for (auto& word : words)
	{
		if (is_number(word))
		{
			sum += std::stol(word);
		}
	}
	return sum;
}

long get_sum_of_ints_in_file(const std::string& filename)
{
	return sum(read_file(filename));
}

int main()
{
	std::cout << "Enter the name of the file: ";
	std::string filename;
	std::cin >> filename;
	try
	{
		auto sum = get_sum_of_ints_in_file(filename);
		std::cout << "Sum: " << sum << '\n';
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}