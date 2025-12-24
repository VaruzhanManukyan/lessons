#include <iostream>
#include "../vector/vector.hpp"
#include "./sorts.hpp"

int main() {
    Vector<int> array = {5, 4, 56, 89, 7, 23, 120, 35, 53};
    mergeSortIterative(array.begin(), array.end());

    for (std::size_t i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " ";
    }

    return 0;
}