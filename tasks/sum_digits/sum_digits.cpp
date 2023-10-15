#include "sum_digits.h"

const int64_t TEN = 10;

int64_t SumOfDigits(int64_t number) {
    int64_t sum = 0;
    while (number) {
        sum += number % TEN;
        number /= TEN;
    }
    return sum;
}