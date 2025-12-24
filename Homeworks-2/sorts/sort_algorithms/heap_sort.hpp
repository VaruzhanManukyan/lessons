#pragma once
#include <vector>

template <typename RandomIterator, typename Compare = std::less<>>
void heapify(RandomIterator begin, std::size_t index, std::size_t heap_size, Compare compare = Compare()) {
    while (true) {
        std::size_t left = index * 2 + 1;
        std::size_t right = left + 1;
        std::size_t largest = index;

        if (left < heap_size && compare(*(begin + largest), *(begin + left))) {
            largest = left;
        }
        if (right < heap_size && compare(*(begin + largest), *(begin + right))) {
            largest = right;
        }

        if (largest == index) {
            return;
        }
        std::iter_swap(begin + index, begin + largest);
        index = largest;
    }
}

template <typename RandomIterator, typename Compare = std::less<>>
void build_max_heapify(RandomIterator begin, RandomIterator end, Compare compare = Compare()) {
    std::size_t size = static_cast<std::size_t>(std::distance(begin, end));
    if (size < 2) {
        return;
    }

    for (std::size_t i = size / 2; i-- > 0;) {
        heapify(begin, i, size, compare);
    }
}

template <typename RandomIterator, typename Compare = std::less<>>
void heap_sort(RandomIterator begin, RandomIterator end, Compare compare = Compare()) {
    std::size_t size = static_cast<std::size_t>(std::distance(begin, end));
    if (size < 2) {
        return;
    }

    build_max_heapify(begin, end, compare);

    for (std::size_t i = size; i-- > 1;) {
        std::iter_swap(begin, begin + i);
        heapify(begin, 0, i, compare);
    }
}