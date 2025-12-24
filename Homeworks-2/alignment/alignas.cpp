#include <iostream>

class A {
    char c;
    int i;
    short s;
};

class alignas(8) B {
    char c;
    int i;
    short s;
};

class C {
    char c;
    alignas(16) int i;
    short s;
};

int main() {
    std::cout << sizeof(A) << "\n"; // 12
    std::cout << sizeof(B) << "\n"; // 16
    std::cout << sizeof(C) << "\n"; // 32

    std::cout << alignof(A) << "\n"; // 4
    std::cout << alignof(B) << "\n"; // 8
    std::cout << alignof(C) << "\n"; // 16

    return 0;
}