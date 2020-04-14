#include <cinttypes>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Reading
{
	uint32_t hour;
	double temp;
	char temp_unit;
};

bool operator==(const Reading& lhs, const Reading& rhs)
{
	return lhs.hour == rhs.hour && lhs.temp == rhs.temp;
}

bool operator!=(const Reading& lhs, const Reading& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const Reading& lhs, const Reading& rhs)
{
	return lhs.temp < rhs.temp;
}

bool operator>(const Reading& lhs, const Reading& rhs)
{
	return lhs.temp > rhs.temp;
}

std::istream& operator>>(std::istream& is, Reading& r)
{
	uint32_t hour{ 0 };
	double temp{ 0 };
	char temp_unit;
	is >> hour >> temp >> temp_unit;
	if (!is)
	{
		return is;
	}
	if (!(temp_unit == 'f' || temp_unit == 'c'))
	{
		throw std::runtime_error(std::string(1, temp_unit) 
			+ " is not a valid temperature unit.");
	}
	r.hour = hour;
	r.temp = temp;
	r.temp_unit = temp_unit;
	return is;
}

double celc_to_fahr(double c)
{
	return c * (9 / 5.0) + 32;
}

double fahr_to_celc(double f)
{
	return (f - 32) / (9 / 5.0);
}

std::vector<Reading> get_readings_from_file(const std::string& file_name)
{
	static const auto invalid_temp{ UINT32_MAX };
	static const auto invalid_hour{ 25 };
	static const auto invalid_temp_unit{ 'k' };
	std::ifstream ifs{ file_name };
	if (!ifs)
	{
		throw std::runtime_error("'" + file_name + "' could not be opened for reading.");
	}
	std::vector<Reading> readings;
	Reading r;
	while (ifs >> r && !ifs.eof())
	{
		if (r.temp_unit == 'f')
		{
			r.temp = fahr_to_celc(r.temp);
		}
		readings.push_back(r);
		r.temp = invalid_temp;
		r.hour = invalid_hour;
		r.temp_unit = invalid_temp_unit;
	}
	return readings;
}

double get_mean_temp(const std::vector<Reading>& readings)
{
	if (readings.empty())
	{
		throw std::runtime_error("Empty vector supplied");
	}
	double sum{ 0 };
	for (auto& reading : readings)
	{
		sum += reading.temp;
	}
	return sum / readings.size();
}

double get_median_temp(const std::vector<Reading>& readings)
{
	if (readings.empty())
	{
		throw std::runtime_error("Empty vector supplied");
	}
	auto size = readings.size();
	if (size == 1)
	{
		return readings.at(0).temp;
	}
	auto readings_copy{ readings };
	std::sort(readings_copy.begin(), readings_copy.end());
	auto pos = readings_copy.size() / 2;
	if (size % 2 != 0)
	{
		return readings_copy.at(pos).temp;
	}
	else
	{
		return (readings_copy.at(pos).temp + readings_copy.at(pos + 1).temp) / 2;
	}
}


int main()
{
	const char* file_name{ "raw_temps.txt" };
	try
	{
		auto readings = get_readings_from_file(file_name);
		auto mean = get_mean_temp(readings);
		auto median = get_median_temp(readings);
		std::cout << "Median temperature: " << median
			<< ", mean temperature: " << mean << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}