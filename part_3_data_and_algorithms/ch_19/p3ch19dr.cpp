#include <vector>
#include <string>
#include <iostream>

template <typename T>
struct S
{
    S(const T &val): val(val) {}
    T &get();
    const T &get() const;
    void set(const T &val)
    {
        this->val = val;
    }

    S &operator=(const T &val)
    {
        this->val = val;
        return *this;
    }
    T val;
};

template <typename T>
T &S<T>::get()
{
    return val;
}

template <typename T>
const T &S<T>::get() const
{
    return val;
}

template <typename T>
std::istream &operator>>(std::istream &in, std::vector<T> &vec)
{
    T val;
    char ch = 0;
    in >> ch;
    if (ch != '{')
        return in;

    while (true) {
        in >> val;
        vec.push_back(val);
        in >> ch;

        if (ch == '}')
            break;
        else if (ch == ',')
            continue;
        else if (!std::isdigit(ch))
            break;
    }

    return in;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &vec)
{
    out << "{";
    for (size_t i = 0; i < vec.size(); ++i) {
        out << vec[i];
        if (i != vec.size() - 1)
            out << ", ";
    }
    out << "}";
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const S<T> &s)
{
    out << s.get();
    return out;
}

template <typename T>
void read_val(T &v)
{
    std::cin >> v;
}

int main()
{
    int ri = 0;
    char ci = 0;
    double di = 0;
    std::string si;
    std::vector<int> vi;
//    std::cin >> ri >> ci >> di >> si >> vi;
    read_val(ri);
    read_val(ci);
    read_val(di);
    read_val(si);
    read_val(vi);


    S<int> sint(ri);
    S<char> schar(ci);
    S<double> sdouble(di);
    S<std::string> sstring(si);
    S<std::vector<int>> svector(vi);

    std::cout << sint << '\n'
        << schar << '\n'
        << sdouble << '\n'
        << sstring << '\n'
        << svector << '\n'
        << std::endl;

    sint = 100;
    schar = 'B';
    sdouble = 2.7;
    sstring = "Live is wonderful";
    svector = { 10, 20, 30 };

    std::cout << sint << '\n'
        << schar << '\n'
        << sdouble << '\n'
        << sstring << '\n'
        << svector << '\n'
        << std::endl;
}
