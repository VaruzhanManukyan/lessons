#include <iterator>
#include <vector>
#include <algorithm>

template <typename RandomIt>
void counting_sort(RandomIt first, RandomIt last) {
    if (first == last) return;

    using T = typename std::iterator_traits<RandomIt>::value_type;

    // 1. Находим минимум и максимум.
    auto [mn_it, mx_it] = std::minmax_element(first, last);
    T mn = *mn_it;
    T mx = *mx_it;

    size_t range = static_cast<size_t>(mx - mn + 1);

    // 2. Создаём массив подсчёта.
    std::vector<size_t> count(range, 0);

    // 3. Подсчёт каждого элемента.
    for (auto it = first; it != last; ++it) {
        count[*it - mn]++;
    }

    // 4. Запись результата обратно в диапазон.
    auto it = first;
    for (size_t i = 0; i < range; ++i) {
        while (count[i] > 0) {
            *it = static_cast<T>(i + mn);
            ++it;
            --count[i];
        }
    }
}
