#include "roman_int.hpp"
#include "generate_check_files.hpp"

#include <iostream>
#include <map>
#include <cassert>
#include <sstream>

int main()
{
	try
	{
		auto file_name{ "problem_6_test.txt" };
		generate_test_file(file_name);
		auto test_map = read_test_file(file_name);
		for (auto it = test_map.begin(); it != test_map.end(); ++it)
		{
			Roman_int rint{ it->second };
			auto as_int = rint.as_int();
			auto compare_with = it->first;
			auto as_str = it->second;
			std::stringstream ss;
			ss << as_str << " == " << as_int;
			assert((ss.str(), compare_with == as_int));
		}
		
		std::cout << "Test passed\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}