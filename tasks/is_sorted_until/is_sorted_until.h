#pragma once

template <typename T>
T IsSortedUntil(T begin, T end) {
    ++begin;
    for (; begin < end; ++begin) {
        if (*begin < *(begin - 1)) {
            return begin;
        }
    }
    return end;
}
