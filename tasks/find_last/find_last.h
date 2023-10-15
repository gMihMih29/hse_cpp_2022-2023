#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    Iterator answer = last;
    for (; first < last; ++first) {
        if (*first == val) {
            answer = first;
        }
    }
    return answer;
}
