#include <iostream>
#include <vector>
#include <memory>

class FenwickTree {
private:
    std::size_t size;
    std::vector<int> bit;

    int query(std::size_t index) const {
        int sum = 0;
        while (index > 0) {
            sum += bit[index];
            index -= (index & -index);
        }
        return sum;
    }

public:
    explicit FenwickTree(std::size_t size) : size(size) {
        bit.assign(size + 1, 0);
    }

    void update(std::size_t index, int delta = 1) {
        while (index <= size) {
            bit[index] += delta;
            index += (index & -index);
        }
    }

    int rangeQuery(std::size_t leftIndex, std::size_t rightIndex) const {
        if (leftIndex > rightIndex) return 0;
        return query(rightIndex) - query(leftIndex - 1);
    }
};

std::string countBribe(const std::vector<int>& array) {
    std::size_t size = array.size();
    std::unique_ptr<FenwickTree> BIT = std::make_unique<FenwickTree>(size);
    long long bribes = 0;

    for (std::size_t i = 0; i < size; ++i) {
        if (array[i] - static_cast<int>(i) - 1 > 2) {
            return "Too chaotic";
        }
        bribes += BIT->rangeQuery(array[i] + 1, size);
        BIT->update(array[i]);
    }

    return std::to_string(bribes);
}

int main() {
    std::vector<int> array = {2, 1, 5, 4, 3};
    std::string result = countBribe(array);
    std::cout << result << "\n";
    return 0;
}
