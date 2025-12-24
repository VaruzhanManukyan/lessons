#include <chrono>
#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <algorithm>
#include <string>

#include "./sorts.hpp"

constexpr std::array<std::size_t, 8> TEST_SIZE = {
    10, 50, 100, 500, 1000, 5000, 10000, 50000
};

std::random_device random_device;
std::mt19937 generator(random_device());
constexpr std::size_t MAX_SIZE = TEST_SIZE[TEST_SIZE.size() - 1];
std::uniform_int_distribution<int> distribution(0, static_cast<int>(MAX_SIZE - 1));

template <typename T>
void arrays_initializer(std::vector<T>& array_random, std::vector<T>& array_sorted_to_largest, std::vector<T>& array_sorted_to_smallest) {
    std::size_t size = array_random.size();

    for (std::size_t i = 0; i < size; ++i) {
        array_sorted_to_largest[i] = static_cast<T>(i);
        array_random[i] = static_cast<T>(distribution(generator));
        array_sorted_to_smallest[i] = static_cast<T>(size - i - 1);
    }
}

template <typename SortFunc>
void time_sort_and_print(const std::string& sort_name, SortFunc sort_func, std::vector<int>& array_to_sort, const std::vector<int>& array_original, std::size_t size) {

    double total_duration = 0.0;
    const int num_runs = 5;

    for (int i = 0; i < num_runs; ++i) {
        std::copy(array_original.begin(), array_original.begin() + size, array_to_sort.begin());

        auto begin = std::chrono::high_resolution_clock::now();
        sort_func(array_to_sort.begin(), array_to_sort.begin() + size);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - begin;
        total_duration += duration.count();
    }

    double average_duration = total_duration / num_runs;

    std::cout << sort_name << " (Size " << size << "): " << (average_duration * 1000.0) << " ms\n";
}

int main() {
    std::vector<int> array_random(MAX_SIZE);
    std::vector<int> array_sorted_to_largest(MAX_SIZE);
    std::vector<int> array_sorted_to_smallest(MAX_SIZE);

    arrays_initializer<int>(array_random, array_sorted_to_largest, array_sorted_to_smallest);

    std::vector<int> array_to_sort(MAX_SIZE);
    std::vector<int> array_original(MAX_SIZE);

    auto merge_wrapper = [](auto begin, auto end) {
        mergeSortIterative(begin, end);
    };

    auto heap_wrapper = [](auto begin, auto end) {
        heap_sort(begin, end, std::less<int>{});
    };

    auto quick_wrapper = [](auto begin, auto end) {
        quick_sort(begin, end, std::less<int>{});
    };

    auto bubble_wrapper = [](auto begin, auto end) {
        bubbleSort(begin, end);
    };

    auto counting_wrapper = [](auto begin, auto end) {
        counting_sort(begin, end);
    };

    std::cout << "\n=== RANDOM NUMBERS (RANDOM) ===\n";
    array_original = array_random; // Устанавливаем исходный массив
    for (const std::size_t SIZE : TEST_SIZE) {
        time_sort_and_print("Merge Sort", merge_wrapper, array_to_sort, array_original, SIZE);
        time_sort_and_print("Heap Sort", heap_wrapper, array_to_sort, array_original, SIZE);
        time_sort_and_print("Quick Sort", quick_wrapper, array_to_sort, array_original, SIZE);
        time_sort_and_print("Bubble Sort", bubble_wrapper, array_to_sort, array_original, SIZE);
        time_sort_and_print("Counting Sort", counting_wrapper, array_to_sort, array_original, SIZE);
    }

    std::cout << "\n=== SORTED TO LARGEST NUMBERS (BEST CASE FOR BUBBLE) ===\n";
    array_original = array_sorted_to_largest; // Устанавливаем исходный массив
    for (const std::size_t SIZE : TEST_SIZE) {
        time_sort_and_print("Merge Sort", merge_wrapper, array_to_sort, array_original, SIZE);
        time_sort_and_print("Heap Sort", heap_wrapper, array_to_sort, array_original, SIZE);
        time_sort_and_print("Quick Sort", quick_wrapper, array_to_sort, array_original, SIZE);
        time_sort_and_print("Bubble Sort", bubble_wrapper, array_to_sort, array_original, SIZE);
        time_sort_and_print("Counting Sort", counting_wrapper, array_to_sort, array_original, SIZE);
    }

    std::cout << "\n=== SORTED TO SMALLEST NUMBERS (WORST CASE FOR BUBBLE) ===\n";
    array_original = array_sorted_to_smallest;
    for (const std::size_t SIZE : TEST_SIZE) {
        time_sort_and_print("Merge Sort", merge_wrapper, array_to_sort, array_original, SIZE);
        time_sort_and_print("Heap Sort", heap_wrapper, array_to_sort, array_original, SIZE);
        time_sort_and_print("Quick Sort", quick_wrapper, array_to_sort, array_original, SIZE);
        time_sort_and_print("Bubble Sort", bubble_wrapper, array_to_sort, array_original, SIZE);
        time_sort_and_print("Counting Sort", counting_wrapper, array_to_sort, array_original, SIZE);
    }

    return 0;
}
