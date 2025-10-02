#include <iostream>
#include "list.hpp"

int main() {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);

    for (auto iterator = list.begin(); iterator != list.end(); ++iterator) {
        std::cout << *iterator << " ";
    }
    std::cout << "\n";
}
