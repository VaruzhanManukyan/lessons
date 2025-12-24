#include <iostream>
#include <vector>
#include <utility>

template <typename Iterator, typename T>
std::pair<T, T> findTwoUniqElement(Iterator begin, Iterator end) {
    T xorAll = 0;
    for (Iterator it = begin; it != end; ++it) {
        xorAll ^= *it;
    }

    T differentBit = xorAll & -xorAll;
    T uniq1 = 0, uniq2 = 0;
    for (Iterator it = begin; it != end; ++it) {
        if (*it & differentBit) {
            uniq1 ^= *it;
        } else {
            uniq2 ^= *it;
        }
    }

    return std::make_pair(uniq1, uniq2);
}

int main() {
    std::vector<int> array = {2, 3, 5, 4, 5, 4, 9, 3, 2, 15};
    auto [uniq1, uniq2] = findTwoUniqElement<std::vector<int>::iterator, int>(array.begin(), array.end());
    std::cout << uniq1 << " " << uniq2 << std::endl;
    return 0;
}