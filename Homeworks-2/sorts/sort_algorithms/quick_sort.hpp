#pragma once
#include <functional>

template <typename RandomIterator, typename Compare>
RandomIterator hoare_partition(RandomIterator first, RandomIterator last, Compare compare) {
    --last;

    auto pivot = *(first + (last - first) / 2);

    RandomIterator i = first;
    RandomIterator j = last;

    while (true) {
        while (compare(*i, pivot)) {
            ++i;
        }
        while (compare(pivot, *j)) {
            --j;
        }

        if (i >= j)
            return j;

        std::iter_swap(i, j);
        ++i; --j;
    }
}

template <typename RandomIterator, typename Compare = std::less<typename std::iterator_traits<RandomIterator>::value_type>>
void quick_sort (RandomIterator first, RandomIterator last, Compare compare = Compare()) {
    if (first == last || std::distance(first, last) <= 1) {
        return;
    }

    RandomIterator pivot = hoare_partition<RandomIterator, Compare>(first, last, compare);
    quick_sort(first, std::next(pivot), compare);
    quick_sort(std::next(pivot) , last, compare);
}