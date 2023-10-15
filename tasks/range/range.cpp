#include "range.h"

#include <cmath>

std::vector<int> Range(int from, int to, int step) {
    if ((to - from) * static_cast<int64_t>(step) <= 0) {
        return std::vector<int>(0);
    }
    std::vector<int> result;
    result.reserve(std::abs(to - from) / std::abs(step));
    if (step > 0) {
        for (; from < to; from += step) {
            result.push_back(from);
        }
    } else {
        for (; from > to; from += step) {
            result.push_back(from);
        }
    }
    return result;
}
