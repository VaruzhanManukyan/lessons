#include <iostream>

#if __cplusplus < 201103L
#error "Your compiler does not support C++11 or newer. Please update your compiler or use -std=c++11 (or higher)."
#endif

int main() {
    std::cout << "C++ version is ok: " << __cplusplus << std::endl;
    return 0;
}