#pragma once
#include <vector>

template<typename Iterator>
void bubbleSort(Iterator begin, Iterator end) {
    std::size_t size = std::distance(begin, end);

    for (std::size_t i = 0; i < size; ++i) {
        Iterator iterator1 = begin;
        Iterator iterator2 = begin + 1;
        for (std::size_t j = 0; j < size - i - 1; ++j) {
            if (*iterator1 > *iterator2) {
                std::swap(*iterator1, *iterator2);
            }
            ++iterator1;
            ++iterator2;
        }
    }
}