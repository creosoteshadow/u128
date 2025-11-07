# u128
Header-only, portable 128-bit unsigned integer for C++17+. Fast intrinsics when available, verified 64×64→128 mul fallback. Full operators, constexpr where possible.

# u128 – portable 128-bit unsigned integer

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)]()

A single-header, header-only implementation of a **128-bit unsigned integer** (`u128`) that works on any 64-bit platform **without** requiring compiler-specific 128-bit types.

* **Fast path** – uses `_umul128` on MSVC and `__int128` on GCC/Clang when available.  
* **Portable fallback** – a pure 64-bit arithmetic `mul64_portable` that has been exhaustively verified against the hardware intrinsic.  
* Full set of arithmetic, bitwise, shift, and comparison operators.  
* `constexpr` where possible (shifts, adds, bitwise ops).  
* `std::ostream` and `std::hash` support.

---

## Why another uint128?

* **Zero dependencies** – just `<cstdint>` and the standard library.  
* **Explicit overflow semantics** – addition and multiplication wrap modulo 2¹²⁸ (just like `uint64_t`).  
* **Verified portable multiplication** – 10 000 random + corner-case tests run at compile-time when `EnablePortableMultiplyVerification` is `1`.  
* **Header-only** – drop `u128.h` into any project.

---

## Quick start

#include "u128.h"
#include <iostream>

int main() {
    using namespace u128;

    u128 a = 0xFFFFFFFFFFFFFFFFULL;          // 2⁶⁴-1
    u128 b = a * a;                           // (2⁶⁴-1)² → wraps
    std::cout << a << " * " << a << " = " << b << '\n';

    u128 c = (u128(1) << 100) + 42;
    std::cout << "1<<100 + 42 = " << c << '\n';
}

Output (hex, zero-padded to 32 digits):

0x0000000000000000ffffffffffffffff * 0x0000000000000000ffffffffffffffff = 0x00000000000000000000000000000001
1<<100 + 42 = 0x0000000000000010000000000000002a

## API oveview

Category        Operators / Functions
Construction    u128(), u128(u64 lo), u128(u64 lo, u64 hi)"
Assignment      operator=(u64)
Arithmetic      +, +=, *, *= (mod 2¹²⁸)
Bitwise         &, `
Comparison      ==, !=, <, <=, >, >="
Printing        to_string_hex(), operator<< (hex), to_string() (decimal, hi_lo format)"
Constants       u128::ZERO, u128::ONE, u128::MAX
Free functions  mul64(u64 a, u64 b), mul64_portable(u64 a, u64 b), add64(u64 a, u64 b)"

## Portable multiplication verification (optional)
    Set the macro before including the header:

    #define EnablePortableMultiplyVerification 1
    #include "u128.h"

    The header will compile a self-test (U128::test_product()) that runs 10 000 random and several deterministic corner cases, printing any mismatch. The test uses _umul128 on MSVC as the reference; on other compilers it is a no-op.

## Building & testing

    # Clone
    git clone https://github.com/<you>/u128.git
    cd u128

    # Compile a tiny demo
    c++ -std=c++17 -I. -O2 demo.cpp -o demo && ./demo

    # Run the verification (MSVC only)
    cl /EHsc /std:c++17 /I. test.cpp && test.exe

A CMakeLists.txt is provided for convenience:

    cmake -B build -S .
    cmake --build build --config Release
    ctest --output-on-failure

## Compatibility

    Compiler        Intrinsic path      Portable path
    MSVC            _umul128_           fallback
    GCC/CLang       __int128            fallback
    any other       none                always portable

    Tested on:
        Visual C++ 2022
    
## License
    MIT – see LICENSE.

## Contributing

    Open an issue for bugs or feature requests.
    Pull requests welcome – please add tests for any new operator.
