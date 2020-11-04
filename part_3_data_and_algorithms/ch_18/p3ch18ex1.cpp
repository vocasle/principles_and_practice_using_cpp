#include <cstddef>
#include <cstdio>

// duplicates C string
char* strdup(const char* str) {
    // check for nullptr
    if (!str) {
        return nullptr;
    }
    // get size of C string
    size_t size = 0;
    while(*str) {
        size++;
        str++;
    }
    // + 1 here to add space for \0 character
    char* s = new char[size + 1];
    // move pointer to the start of the string
    str -= size;
    while(*str) {
        *s++ = *str++;
    }
    // add terminating character
    *s = '\0';
    // move pointer to the start of the string
    s -= size;
    return s;
}

int main() {
    const char* s1 = "Hello";
    std::puts(s1);
    char* s2 = strdup(s1);
    std::puts(s2);
}