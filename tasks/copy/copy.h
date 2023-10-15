#pragma once

template <typename T, typename U>
U Copy(T src_begin, T src_end, U dest) {
    for (; src_begin < src_end; ++src_begin, ++dest) {
        *dest = *src_begin;
    }
    return dest;
}

template <typename T, typename U>
U CopyBackward(T src_begin, T src_end, U dest) {
    --src_end;
    --dest;
    for (; src_begin <= src_end; --src_end, --dest) {
        *dest = *src_end;
    }
    return ++dest;
}