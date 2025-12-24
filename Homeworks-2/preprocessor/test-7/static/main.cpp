#include <iostream>
#include "config.h"

void foo_1();
void foo_2();

int main() {
    foo_1();
    foo_2();

    std::cout << globalCounter << std::endl;

    return 0;
}