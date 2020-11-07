#include <cstddef>

size_t strlen(const char* str) {
    if (!str) {
      return 0;
    }
    size_t size = 0;
    while (*str) {
      size++;
      str++;
    }
    return size + 1;
}

// compares two C strings
int strcmp(const char* s1, const char* s2, size_t limit) {
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

// duplicates C string
char *strdup(const char *str, size_t limit) {
  // check for nullptr
  if (!str) {
    return nullptr;
  }
  // get size of C string
  size_t size = strlen(str);
  char *s = new char[size];
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
char *findx(const char *s, const char *x, size_t limits) {
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
        return strdup(pos, strlen(pos));
      }
    }
     x = xbegin;
  }
  return nullptr;
}

int main() {
  strdup("hello", strlen("hello"));
}
