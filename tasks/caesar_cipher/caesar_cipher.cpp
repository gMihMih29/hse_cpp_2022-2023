#include "caesar_cipher.h"

const int ALPHABET_LENGTH = 'Z' - 'A' + 1;

std::string Decipher(const std::string& cipher, size_t shift) {
    std::string result = cipher;
    int symbol_number = 0;
    shift %= ALPHABET_LENGTH;
    for (size_t i = 0; i < cipher.length(); ++i) {
        symbol_number = cipher[i] - 'A';
        symbol_number += ALPHABET_LENGTH - static_cast<int>(shift);
        symbol_number %= ALPHABET_LENGTH;
        result[i] = static_cast<char>(symbol_number + 'A');
    }
    return result;
}