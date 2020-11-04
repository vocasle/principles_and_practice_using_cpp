#include <iostream>

// compares two C strings
// returns negative int if s1 is lexicographically is less than s2
// positive int if s1 is greater than s2
// otherwise returns 0
int strcmp(const char* s1, const char* s2) {
    if (!s1 || !s2) {
        return 0;
    }
    int result = 0;
    while(*s1 && *s2) {
        result = *s1 - *s2;
        if (result) {
            return result;
        }
        ++s1;
        ++s2;
    }
    return 0;
}

int main() {
    const char* s1 = "banana";
    const char* s2 = "Banana";
    std::cout << strcmp(s1, s2) << std::endl;
}