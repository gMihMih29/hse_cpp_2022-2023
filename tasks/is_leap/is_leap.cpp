#include "is_leap.h"

const int FOUR = 4;
const int HUNDRED = 100;
const int FOUR_HUNDRED = 400;

bool IsLeap(int year) {
    if (year % FOUR_HUNDRED == 0) {
        return true;
    }
    if (year % FOUR == 0 && year % HUNDRED != 0) {
        return true;
    }
    return false;
}
