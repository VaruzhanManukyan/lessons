#include <iostream>

#pragma pack(push, 1)
class A {
    char c;
    int i;
    short s;
};
#pragma pack(pop)

#pragma pack(2)
class B {
    char c;
    int i;
    short s;
};

class C {
    int i;
    short s;
    char c;
};

int main() {
    std::cout << sizeof(A) << "\n"; // 7
    std::cout << sizeof(B) << "\n"; // 8
    std::cout << sizeof(C) << "\n"; // 8

    std::cout << alignof(A) << "\n"; // 1
    std::cout << alignof(B) << "\n"; // 2
    std::cout << alignof(C) << "\n"; // 2
    
    return 0;
}