#include <iostream>

#define MAX(a, b) (a > b ? a : b)

template <typename T>
inline T max_inline(const T& a, const T& b) {
    return a > b ? a : b;
}

int main () {
    int x = 1, y = 1;
    int first_result = MAX(x++, y++);
    std::cout << first_result << std::endl;

    x = 1, y = 1;
    int second_result = max_inline(x++, y++);
    std::cout << second_result << std::endl;
}