#include <iostream>
#include <vector>

template <typename Iterator, typename T>
T findUniqElement(Iterator begin, Iterator end) {
    T result = 0;
    for (Iterator it = begin; it != end; ++it) {
        result ^= *it;
    }
    return result;
}

int main() {
    std::vector<int> array = {2, 3, 5, 4, 5, 4, 9, 3, 2};
    int uniq = findUniqElement<std::vector<int>::iterator, int>(array.begin(), array.end());
    std::cout << uniq << std::endl;
    return 0;
}