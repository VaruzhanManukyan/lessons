#include <chrono>
#include <iostream>
#include <random>
#include <array>
#include "../vector/vector.hpp"
#include "./sorts.hpp"

constexpr std::array<std::size_t, 9> TEST_SIZE = {
    10, 50, 100, 500, 1000, 5000, 10000, 50000, 1000000
};

std::random_device random_device;
std::mt19937 generator(random_device());
std::uniform_int_distribution<int> distribution(0, static_cast<size_t>(TEST_SIZE[TEST_SIZE.size() - 1]) - 1);

template <typename T>
void arrays_initializer(Vector<T>& array_random, Vector<T>& array_sorted_to_largest, Vector<T>& array_sorted_to_smallest, const std::size_t testSize) {
    std::size_t size = static_cast<std::size_t>(testSize);
    for (std::size_t i = 0; i < size; ++i) {
        array_random[i] = distribution(generator);
        array_sorted_to_largest[i] = i;
        array_sorted_to_smallest[i] = size - i - 1;
    }
}

int main() {
    Vector<int> array_random(static_cast<std::size_t>(TEST_SIZE[TEST_SIZE.size() - 1]));
    Vector<int> array_sorted_to_largest(static_cast<std::size_t>(TEST_SIZE[TEST_SIZE.size() - 1]));
    Vector<int> array_sorted_to_smallest(static_cast<std::size_t>(TEST_SIZE[TEST_SIZE.size() - 1]));

    for (const std::size_t SIZE : TEST_SIZE) {
        arrays_initializer<int>(array_random, array_sorted_to_largest, array_sorted_to_smallest, SIZE);
        std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
        mergeSortIterative(array_random.begin(), array_random.begin() + SIZE);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
        std::cout << "Time elapsed marge sort: " << duration.count() << " seconds\n";

        arrays_initializer<int>(array_random, array_sorted_to_largest, array_sorted_to_smallest, SIZE);
        begin = std::chrono::high_resolution_clock::now();
        bubbleSort(array_random.begin(), array_random.begin() + SIZE);
        end = std::chrono::high_resolution_clock::now();

        duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
        std::cout << "Time elapsed bubble sort: " << duration.count() << " seconds\n";
    }

    return 0;
}