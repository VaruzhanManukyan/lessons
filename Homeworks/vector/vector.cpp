#include <iostream>
#include "vector.hpp"

int main() {
    Vector<int> array;

    for (int i = 1; i <= 10; ++i) {
        array.push_back(i);
        std::cout << "push " << i
                  << " -> size=" << array.size()
                  << ", capacity=" << array.capacity() << '\n';
    }

    std::cout << "--- resize down ---\n";
    array.resize(5, 0);
    std::cout << "size=" << array.size() << ", capacity=" << array.capacity() << '\n';

    std::cout << "--- shrink_to_fit ---\n";
    array.shrink_to_fit();
    std::cout << "size=" << array.size() << ", capacity=" << array.capacity() << '\n';

    std::cout << "--- elements ---\n";
    for (std::size_t i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << '\n';
}