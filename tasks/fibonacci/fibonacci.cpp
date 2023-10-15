#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t prev_number = 0;
    int64_t cur_number = 1;
    int64_t memory_number = 0;
    if (n == 0) {
        return prev_number;
    }
    if (n == 1) {
        return cur_number;
    }
    for (int64_t i = 2; i <= n; ++i) {
        memory_number = cur_number;
        cur_number += prev_number;
        prev_number = memory_number;
    }
    return cur_number;
}
