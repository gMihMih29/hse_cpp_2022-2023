#pragma once

#include <algorithm>

template <typename Iterator>
void Reverse(Iterator begin, Iterator end) {
    for (size_t i = 0; i < (end - begin) / 2; ++i) {
        std::swap(*(begin + i), *(end - i - 1));
    }
}

template <typename Iterator>
void Rotate(Iterator begin, Iterator mid, Iterator end) {
    Reverse(begin, mid);
    Reverse(mid, end);
    Reverse(begin, end);
}
