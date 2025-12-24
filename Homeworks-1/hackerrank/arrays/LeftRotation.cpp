#include <iostream>
#include <vector>

template <typename T>
void swap(T& first, T& last) {
    T temp = std::move(first);
    first = std::move(last);
    last = std::move(temp);
}


void leftShift(std::vector<int>& array, int shift) {
    int size = array.size();
    if (size == 0) return;

    shift %= size;
    if (shift == 0) return;

    int begin = 0;
    int end = shift - 1;
    while (begin < end) {
        swap(array[begin], array[end]);
        ++begin;
        --end;
    }

    begin = shift;
    end = size - 1;
    while (begin < end) {
        swap(array[begin], array[end]);
        ++begin;
        --end;
    }

    begin = 0;
    end = size - 1;
    while (begin < end) {
        swap(array[begin], array[end]);
        ++begin;
        --end;
    }
}

int main() {
    std::vector<int> array = {1, 2, 3, 4, 5};
    leftShift(array, 2);
    for (int item : array) {
        std::cout << item << ' ';
    }
    return 0;
}