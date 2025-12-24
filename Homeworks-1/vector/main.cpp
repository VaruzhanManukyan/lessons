#include <iostream>
#include "vector.hpp"

int main() {
    std::cout << a << std::endl;

    Vector<int> array;

    for (int i = 1; i <= 5; ++i) {
        array.push_back(i);
        std::cout << "push " << i
                  << " -> size=" << array.size()
                  << ", capacity=" << array.capacity() << '\n';
    }

    std::cout << "\n--- before insert ---\n";
    for (std::size_t i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";

    std::cout << "\nInsert 100 at beginning:\n";
    array.insert(array.begin(), 100);
    for (std::size_t i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";

    // Insert in the middle
    std::cout << "\nInsert 200 in the middle:\n";
    array.insert(array.begin() + 3, 200);
    for (std::size_t i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";

    // Insert at the end
    std::cout << "\nInsert 300 at the end:\n";
    array.insert(array.end(), 300);
    for (std::size_t i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";

    std::cout << "\nFinal size=" << array.size()
              << ", capacity=" << array.capacity() << '\n';

    return 0;
}
