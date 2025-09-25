#include <iostream>
#include <map>
#include <vector>
#include <climits>

struct Query {
    long long a, b, k;
};

long long findMax(std::vector<Query>&& queries, long long n) {
    std::map<long long, long long> events;

    for (auto& query : queries) {
        events[query.a] += query.k;
        events[query.b + 1] -= query.k;
    }

    long long currentSum = 0;
    long long maxValue = LLONG_MIN;

    for (auto& event : events) {
        currentSum += event.second;
        if (currentSum > maxValue) {
            maxValue = currentSum;
        }
    }
    if (maxValue == LLONG_MIN) return 0;
    return maxValue;
}

int main() {
    long long size = 10;
    std::vector<Query> array = {
        {1, 3, 5},
        {4, 7, 10},
        {2, 9, 3}
    };

    long long result = findMax(std::move(array), size);
    std::cout << result << std::endl;

    return 0;
}
