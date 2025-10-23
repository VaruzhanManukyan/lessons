#include <iostream>
#include <vector>

template <typename T>
void swap(T& first, T& last) {
    T temp = std::move(first);
    first = std::move(last);
    last = std::move(temp);
}

int countSwap(std::vector<int>& array) {
    std::size_t size = array.size();
    std::size_t swapCount = 0;

    for (std::size_t i = 0; i < size; ++i) {
        while (array[i] != static_cast<int>(i) + 1) {
            swap(array[i], array[array[i] - 1]);
            ++swapCount;
        }
    }

    return swapCount;
}

int main() {
    std::vector<int> array = {7, 1, 3, 2, 4, 5, 6};
    std::cout << countSwap(array);
    return 0;
}