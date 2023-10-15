#pragma once

template <typename T, typename U>
T Remove(T begin, T end, U value) {
    T values_to_remove_iter = begin;
    for (; begin < end; ++begin) {
        if (*begin != value) {
            auto temp = *values_to_remove_iter;
            *values_to_remove_iter = *begin;
            *begin = temp;
            ++values_to_remove_iter;
        }
    }
    return values_to_remove_iter;
}
