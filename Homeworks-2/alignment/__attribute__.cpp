#include <iostream>

class A {
    char c;
    int i;
    short s;
};

class __attribute__((packed)) B {
    char c;
    int i;
    short s;
};

class C {
    char c;
    __attribute__((packed)) int i;
    short s;
};

class __attribute__((packed, aligned(16))) D {
    char c;
    int i;
    short s;
};

class E {
    char c;
     __attribute__((packed, aligned(8))) int i;
    short s;
};

int main() {
    std::cout << sizeof(A) << "\n"; // 12
    std::cout << sizeof(B) << "\n"; // 7
    std::cout << sizeof(C) << "\n"; // 8
    std::cout << sizeof(D) << "\n"; // 16
    std::cout << sizeof(E) << "\n"; // 16

    std::cout << alignof(A) << "\n"; // 4
    std::cout << alignof(B) << "\n"; // 1
    std::cout << alignof(C) << "\n"; // 2
    std::cout << alignof(D) << "\n"; // 16
    std::cout << alignof(E) << "\n"; // 8
    return 0;
}