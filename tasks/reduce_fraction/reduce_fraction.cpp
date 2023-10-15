#include "reduce_fraction.h"

int64_t GreatestCommonDivisor(int64_t a, int64_t b) {
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    while (a > 0 && b > 0) {
        if (a > b) {
            a %= b;
        } else {
            b %= a;
        }
    }
    return a + b;
}

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t gcd = GreatestCommonDivisor(numerator, denominator);
    if (denominator < 0) {
        denominator = -denominator;
        numerator = -numerator;
    }
    numerator /= gcd;
    denominator /= gcd;
    return numerator + denominator;
}
