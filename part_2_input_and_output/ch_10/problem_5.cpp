#include <iostream>
#include <vector>
#include <random>
#include <string>

const int not_a_month{ -1 };
const int not_a_reading{ 7777 }; // less than absolute zero

std::vector<std::string> month_input_tbl {
    "jan", "feb", "mar", "apr", "may", "jun", "jul",
    "aug", "sep", "oct", "nov", "dec"
};

std::string int_to_month(int i)
// months [0:11]
{
    if (i < 0 || 12 <= i)
    {
        throw std::runtime_error("bad month index");
    }
    return month_input_tbl[i];
}

struct Day {
    std::vector<double> hour = std::vector<double>(24, not_a_reading);
};

struct Month { // a month of temperature readings
    int month{ not_a_month }; // [0:11] January is 0
    std::vector<Day> day{ 32 }; // [1:31] one vector of readings per day
};

struct Year { // a year of temperature readings, organized by month
    int year; // positive == A.D.
    std::vector<Month> month{ 12 }; // [0:11] January is 0
};

void print_reading(std::ostream& os, const Day& d, uint32_t day_of_month)
{
    auto hour_cnt = 0;
    for (auto& temp : d.hour)
    {
        if (temp != not_a_reading)
        {
            os << "( " << day_of_month << ' ' << hour_cnt << ' ' << temp << " )";
            os << ' ';
            ++hour_cnt;
        }
    }
}

void print_month(std::ostream& os, const Month& m)
{
    if (m.month != not_a_month)
    {
        os << " { month " << int_to_month(m.month) << ' ';
        auto day_cnt = 1;
        for (auto& d : m.day)
        {
            print_reading(os, d, day_cnt);
            ++day_cnt;
        }
        os << "}";
    }
}

void print_year(std::ostream& os, const Year& y)
{
    os << "{ " << y.year;
    for (auto& m : y.month)
    {
        print_month(os, m);
    }
    os << " }\n";
}

double get_random_temp(double min, double max)
{
    std::random_device rd;
    std::uniform_real_distribution<double> urd(min, max);
    std::default_random_engine re{ rd() };
    return urd(re);
}

int32_t get_random_int(int32_t from, int32_t to)
{
    std::random_device rd;
    std::uniform_int_distribution<uint32_t> uid(from, to);
    std::default_random_engine re{ rd() };
    return uid(re);
}

uint32_t get_random_hour()
{
    return get_random_int(0, 23);
}

int main()
{
    std::vector<Day> days{ Day{}, Day{}, Day{} };
    for (auto& day : days)
    {
        day.hour.push_back(get_random_temp(15, 35));
    }
    std::vector<Month> months{ Month{}, Month{} };
    auto m_cnt = 5;
    for (auto& month : months)
    {
        month.day = days;
        month.month = m_cnt++;
    }
    Month m{};
    m.month = 8;
    months.push_back(m);
    std::vector<Year> ys{ Year{}, Year{} };
    auto y_cnt = 1;
    for (auto& year : ys)
    {
        year.month = months;
        year.year = 2019 + y_cnt++;
    }
    Year y{};
    y.year = 2025;
    ys.push_back(y);
    for (auto& y : ys)
    {
        print_year(std::cout, y);
    }
}