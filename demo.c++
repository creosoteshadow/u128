// demo.cpp
#include "u128.h"
#include <iostream>

int main() {
    using namespace u128;
    u128 a = 0xFFFFFFFFFFFFFFFFULL;
    u128 b = a * a;
    std::cout << a << " * " << a << " = " << b << '\n';

    u128 c = (u128(1) << 100) + 42;
    std::cout << "1<<100 + 42 = " << c << '\n';
}
