#include <algorithm>
#include <bits/stdint-uintn.h>
#include <cstddef>
#include <iostream>
#include <vector>

std::vector<int> gv = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

void f(const std::vector<int>& vec) {
  std::vector<int> lv(vec.size());
  lv = gv;
  for (int el : lv) {
      std::cout << el << '\n';
  }

  std::vector<int> lv2 = vec;
  for (int el : lv2) {
      std::cout << el << '\n';
  }
}

uint32_t fact(uint32_t factor) {
    if (factor == 0) {
        return 1;
    }
    uint32_t result = 1;
    for (size_t count = 1; count <= factor; count++) {
        result *= count;
    }
    return result;
}

int main() { 
    constexpr uint32_t size = 10;
    f(gv);
    std::vector<int> vv(size);
    for (size_t count = 0; count < size; count++) {
        vv[count] = fact(count + 1);
    }
    f(vv);
}