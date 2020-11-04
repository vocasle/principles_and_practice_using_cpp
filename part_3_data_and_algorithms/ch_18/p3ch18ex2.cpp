#include <cstddef>
#include <iostream>

// duplicates C string
char *strdup(const char *str) {
  // check for nullptr
  if (!str) {
    return nullptr;
  }
  // get size of C string
  size_t size = 0;
  while (*str) {
    size++;
    str++;
  }
  // + 1 here to add space for \0 character
  char *s = new char[size + 1];
  // move pointer to the start of the string
  str -= size;
  while (*str) {
    *s++ = *str++;
  }
  // add terminating character
  *s = '\0';
  // move pointer to the start of the string
  s -= size;
  return s;
}

// finds substring x of string s
char *findx(const char *s, const char *x) {
  // validate if either of arguments is a nullptr
  if (!s || !x) {
    return nullptr;
  }

  // position of the first character of x
  const char *const xbegin = x;

  while (*s) {
    // position of the first character of current substring of original s
    const char *pos = s;
    if (*s++ == *x++) {
      while (*s && *x && *s == *x) {
        ++s;
        ++x;
      }
      if (*x == '\0') {
        return strdup(pos);
      }
    }
     x = xbegin;
  }
  return nullptr;
}

int main() {
  const char *s1 = "hello, bro!";
  char *s2 = findx(s1, ",");
  if (s2) {
    std::puts(s2);
  }
}