#include "factorization.h"

std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::vector<std::pair<int64_t, int>> result = {};
    int64_t x_memory = x;
    int64_t i = 2;
    int count = 0;
    while (x != 1 && i * i <= x_memory) {
        count = 0;
        while (x % i == 0) {
            x /= i;
            ++count;
        }
        if (count != 0) {
            result.emplace_back(i, count);
        }
        ++i;
    }
    if (x_memory == x) {
        result.emplace_back(x_memory, 1);
    } else if (x != 1) {
        result.emplace_back(x, 1);
    }
    return result;
}
