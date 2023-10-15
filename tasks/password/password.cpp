#include "password.h"

const int MIN_PASSWORD_LENGTH = 8;
const int MAX_PASSWORD_LENGTH = 14;
const int MIN_CHAR = 33;
const int MAX_CHAR = 126;

bool ValidatePassword(const std::string& password) {
    if (MIN_PASSWORD_LENGTH > password.length() || password.length() > MAX_PASSWORD_LENGTH) {
        return false;
    }
    for (const char& i : password) {
        if (i < MIN_CHAR || MAX_CHAR < i) {
            return false;
        }
    }
    bool has_digits = false;
    bool has_upper = false;
    bool has_lower = false;
    bool has_other_symbols = false;
    for (const char& i : password) {
        if (isdigit(i)) {
            has_digits = true;
        } else if (isupper(i)) {
            has_upper = true;
        } else if (islower(i)) {
            has_lower = true;
        } else {
            has_other_symbols = true;
        }
    }
    return has_digits + has_upper + has_lower + has_other_symbols >= 3;
}
