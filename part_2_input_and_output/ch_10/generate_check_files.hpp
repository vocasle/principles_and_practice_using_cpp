#ifndef GENERATE_CHECK_FILES_HPP
#define GENERATE_CHECK_FILES_HPP
#include <string>
#include <map>

void generate_test_file(const std::string& file_name);
std::map<uint32_t, std::string> read_test_file(const std::string& file_name);
std::string val_to_rnum(uint32_t i);
std::string num_to_roman(uint32_t num);
#endif // !GENERATE_CHECK_FILES_HPP
