#include "variable_diagonal.h"

#include <algorithm>

int** BuildDiagonalArray(size_t lines, size_t columns) {
    int** arr = new int*[lines];
    for (size_t i = 0; i < lines; ++i) {
        arr[i] = new int[columns];
    }
    int current_number = 0;
    for (size_t i = 1; i <= columns; ++i) {
        for (size_t j = 0; j < std::min(i, lines); ++j) {
            arr[j][i - j - 1] = current_number++;
        }
    }
    for (size_t i = lines - 1; i >= 1; --i) {
        for (size_t j = 0; j < i; ++j) {
            arr[lines - i + j][lines - j - 1] = current_number++;
        }
    }
    return arr;
}