#include "palindrome.h"

#include <algorithm>

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    size_t l = 0;
    size_t r = str.length() - 1;
    while (l < r) {
        while (str[l] == ' ' && l != str.length() - 1) {
            ++l;
        }
        while (str[r] == ' ' && r != 0) {
            --r;
        }
        if (l >= r) {
            break;
        }
        if (str[l] != str[r]) {
            return false;
        }
        ++l;
        --r;
    }
    return true;
}
