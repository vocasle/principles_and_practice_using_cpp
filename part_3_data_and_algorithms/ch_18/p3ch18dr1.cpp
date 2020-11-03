#include <algorithm>
#include <bits/stdint-uintn.h>
#include <cstddef>
#include <iostream>
int ga[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

void f(int* arr, uint32_t size) {
    int la[10];
    std::copy(ga, &ga[10], la);
    for (size_t count = 0; count < 10; count++) {
        std::cout << la[count] << '\n';
    }
    int* p = new int[size];
    std::copy(arr, &arr[size], p);  
    for (size_t count = 0; count < size; count++) {
        std::cout << p[count] << '\n';
    }
    delete[] p;
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
    f(ga, size);
    int aa[size];
    for (size_t count = 0; count < size; count++) {
        aa[count] = fact(count + 1);
    }
    f(aa, size);
}