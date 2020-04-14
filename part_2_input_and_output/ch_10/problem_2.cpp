// This file contains solution for exercise 2 of chapter 10

#include <random>
#include <fstream>
#include <string>
#include <iostream>

double get_random_temp(double min, double max)
{
	std::random_device rd;
	std::uniform_real_distribution<double> urd(min, max);
	std::default_random_engine re{rd()};
	return urd(re);
}

uint32_t get_random_hour()
{
	std::random_device rd;
	std::uniform_int_distribution<uint32_t> uid(0, 23);
	std::default_random_engine re{ rd() };
	return uid(re);
}

struct Reading
{
	uint32_t hour;
	double temp;
};

Reading generate_reading(double temp_min = -60, double temp_max = 50)
{
	Reading r{};
	r.hour = get_random_hour();
	r.temp = get_random_temp(temp_min, temp_max);
	return r;
}

std::vector<Reading> generate_readings(uint32_t amount)
{
	std::vector<Reading> readings;
	while (readings.size() != amount)
	{
		readings.push_back(generate_reading());
	}
	return readings;
}

void write_readings_to_file(const std::string& file_name,
	const std::vector<Reading>& readings)
{
	std::ofstream ofs{ file_name };
	if (!ofs)
	{
		throw std::runtime_error("'" + file_name + "' could not be opened for writing.");
	}
	for (auto& reading : readings)
	{
		ofs << reading.hour << ' ' << reading.temp << '\n';
	}
}



int main()
{
	const char* file_name{ "raw_temps.txt" };
	write_readings_to_file(file_name, generate_readings(50));
	std::cout << "Temperature readings written to file '" << file_name << "'\n";
}