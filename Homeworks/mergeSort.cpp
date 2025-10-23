#include <iostream>
#include "vector/vector.hpp"

template <typename Iterator>
void merge(Iterator begin, Iterator middle, Iterator end) {
    using Value = typename std::iterator_traits<Iterator>::value_type;
    Vector<Value> buffer;
    buffer.reserve(std::distance(begin, end));

    Iterator iterator1 = begin;
    Iterator iterator2 = middle;

    while(iterator1 != middle && iterator2 != end) {
        if (*iterator1 <= *iterator2) {
            buffer.push_back(*iterator1);
            ++iterator1;
        } else {
            buffer.push_back(*iterator2);
            ++iterator2;
        }
    }

    while (iterator1 != middle) {
        buffer.push_back(*iterator1);
        ++iterator1;
    }

    while (iterator2 != end) {
        buffer.push_back(*iterator2);
        ++iterator2;
    }

    std::copy(buffer.begin(), buffer.end(), begin);
}

template <typename Iterator>
void mergeSortRecursive(Iterator begin, Iterator end) {
    using diff_t = typename std::iterator_traits<Iterator>::difference_type;
    diff_t size = std::distance(begin, end);
    if (size <= 1) {
        return;
    }

    Iterator middle  = begin + size / 2;
    mergeSortRecursive(begin, middle);
    mergeSortRecursive(middle, end);
    merge(begin, middle, end);
}

template <typename Iterator>
void mergeSortIterative(Iterator begin, Iterator end) {
    using diff_t = typename std::iterator_traits<Iterator>::difference_type;
    diff_t size = std::distance(begin, end);
    if (size <= 1) {
        return;
    }

    for (diff_t width = 1; width < size; width *= 2) {
        for (diff_t i = 0; i < size; i += width * 2) {
            diff_t left = i;
            diff_t middle = std::min(i + width, size);
            diff_t right = std::min(i + width * 2, size);

            Iterator leftIterator = begin + left;
            Iterator middleIterator = begin + middle;
            Iterator rightIterator = begin + right;

            if (leftIterator != middleIterator && middleIterator != rightIterator) {
                merge(leftIterator, middleIterator, rightIterator);
            }
        }
    }
}

int main() {
    Vector<int> array = {5, 4, 56, 89, 7, 23, 120, 35, 53};
    mergeSortIterative(array.begin(), array.end());

    for (std::size_t i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " ";
    }

    return 0;
}